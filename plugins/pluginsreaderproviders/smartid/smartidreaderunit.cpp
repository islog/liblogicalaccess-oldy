/**
 * \file smartidreaderunit.cpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief SmartID reader unit.
 */

#include <logicalaccess/plugins/readers/smartid/smartidreaderunit.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

#include <logicalaccess/plugins/readers/smartid/smartidreaderprovider.hpp>
#include <logicalaccess/services/accesscontrol/cardsformatcomposite.hpp>
#include <logicalaccess/cards/chip.hpp>
#include <logicalaccess/plugins/readers/smartid/commands/mifaresmartidcommands.hpp>
#include <logicalaccess/plugins/readers/smartid/readercardadapters/smartidreadercardadapter.hpp>
#include <logicalaccess/plugins/readers/smartid/smartidledbuzzerdisplay.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <logicalaccess/dynlibrary/librarymanager.hpp>
#include <logicalaccess/dynlibrary/idynlibrary.hpp>
#include <logicalaccess/readerproviders/serialportdatatransport.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace logicalaccess
{
SmartIDReaderUnit::SmartIDReaderUnit()
    : ReaderUnit(READER_SMARTID)
{
    d_readerUnitConfig.reset(new SmartIDReaderUnitConfiguration());
    ReaderUnit::setDefaultReaderCardAdapter(std::make_shared<SmartIDReaderCardAdapter>());
    d_ledBuzzerDisplay.reset(new SmartIDLEDBuzzerDisplay());
    std::shared_ptr<SerialPortDataTransport> dataTransport(new SerialPortDataTransport());
    dataTransport->setPortBaudRate(115200);
    ReaderUnit::setDataTransport(dataTransport);
    d_card_type = CHIP_UNKNOWN;

    try
    {
        boost::property_tree::ptree pt;
        read_xml(
            (boost::filesystem::current_path().string() + "/SmartIDReaderUnit.config"),
            pt);
        d_card_type = pt.get("config.cardType", CHIP_UNKNOWN);
    }
    catch (...)
    {
    }
}

SmartIDReaderUnit::~SmartIDReaderUnit()
{
    SmartIDReaderUnit::disconnectFromReader();
}

std::string SmartIDReaderUnit::getName() const
{
    return getDataTransport()->getName();
}

std::string SmartIDReaderUnit::getConnectedName()
{
    return getName();
}

void SmartIDReaderUnit::setCardType(std::string cardType)
{
    d_card_type           = cardType;
    d_readerCommunication = getReaderCommunication(cardType);
    std::dynamic_pointer_cast<ReaderCardAdapter>(d_readerCommunication)
        ->setDataTransport(getDataTransport());
}

std::shared_ptr<ReaderCommunication>
SmartIDReaderUnit::getReaderCommunication(std::string cardType)
{
    std::shared_ptr<ReaderCommunication> ret;

    if (cardType == "Mifare1K" || cardType == "Mifare4K" || cardType == "Mifare")
        ret.reset(new MifareSmartIDReaderCardAdapter());
    else
        ret.reset(new SmartIDReaderCardAdapter());
    return ret;
}

bool SmartIDReaderUnit::waitInsertion(unsigned int maxwait)
{
    bool inserted            = false;
    unsigned int currentWait = 0;

    do
    {
        try
        {
            d_readerCommunication->request();
            d_insertedChip = createChip(d_card_type);
            inserted       = true;
        }
        catch (std::exception &)
        {
            inserted = false;
        }

        if (!inserted)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            currentWait += 500;
        }
    } while (!inserted && currentWait < maxwait);

    return inserted;
}

bool SmartIDReaderUnit::waitRemoval(unsigned int maxwait)
{
    bool removed             = false;
    unsigned int currentWait = 0;

    do
    {
        try
        {
            d_readerCommunication->request();
            removed = false;
        }
        catch (std::exception &)
        {
            removed = true;
        }

        if (!removed)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            currentWait += 500;
        }
    } while (!removed && currentWait < maxwait);

    if (removed)
    {
        d_insertedChip.reset();
    }

    return removed;
}

bool SmartIDReaderUnit::connect()
{
    bool ret;

    resetRF();

    try
    {
        d_readerCommunication->request();
    }
    catch (std::exception &)
    {
    }

    try
    {
        ByteVector uid = d_readerCommunication->anticollision();
        d_readerCommunication->selectIso(uid);

        d_insertedChip->setChipIdentifier(uid);

        ret = true;
    }
    catch (std::exception &)
    {
        ret = false;
    }

    return ret;
}

void SmartIDReaderUnit::disconnect()
{
    resetRF();
}

ByteVector SmartIDReaderUnit::getCardSerialNumber()
{
    ByteVector data;
    data.push_back(static_cast<unsigned char>(0x01));

    ByteVector csn = getDefaultSmartIDReaderCardAdapter()->sendCommand(0x53, data);
    return csn;
}

std::shared_ptr<Chip> SmartIDReaderUnit::createChip(std::string type)
{
    std::shared_ptr<Chip> chip = ReaderUnit::createChip(type);
    setcryptocontext setcryptocontextfct;

    if (chip)
    {
        std::shared_ptr<ReaderCardAdapter> rca;
        std::shared_ptr<Commands> commands;

        if (type == "Mifare1K" || type == "Mifare4K" || type == "Mifare")
        {
            rca.reset(new MifareSmartIDReaderCardAdapter());
            commands.reset(new MifareSmartIDCommands());
        }
        else if (type == "DESFireEV1")
        {
            rca      = getDefaultReaderCardAdapter();
            commands = LibraryManager::getInstance()->getCommands("DESFireEV1ISO7816");
            *(void **)(&setcryptocontextfct) =
                LibraryManager::getInstance()->getFctFromName(
                    "setCryptoContextDESFireEV1ISO7816Commands",
                    LibraryManager::READERS_TYPE);
            setcryptocontextfct(&commands, &chip);
        }
        else if (type == "DESFire")
        {
            rca      = getDefaultReaderCardAdapter();
            commands = LibraryManager::getInstance()->getCommands("DESFireISO7816");
            *(void **)(&setcryptocontextfct) =
                LibraryManager::getInstance()->getFctFromName(
                    "setCryptoContextDESFireEV1ISO7816Commands",
                    LibraryManager::READERS_TYPE);
            setcryptocontextfct(&commands, &chip);
        }
        else if (type == "Twic")
        {
            rca      = getDefaultReaderCardAdapter();
            commands = LibraryManager::getInstance()->getCommands("TwicISO7816");
        }
        else
            return chip;

        rca->setDataTransport(getDataTransport());
        if (commands)
        {
            commands->setReaderCardAdapter(rca);
            commands->setChip(chip);
            chip->setCommands(commands);
        }
    }
    return chip;
}

std::shared_ptr<Chip> SmartIDReaderUnit::getSingleChip()
{
    std::shared_ptr<Chip> chip = d_insertedChip;
    return chip;
}

std::vector<std::shared_ptr<Chip>> SmartIDReaderUnit::getChipList()
{
    std::vector<std::shared_ptr<Chip>> chipList;
    std::shared_ptr<Chip> singleChip = getSingleChip();
    if (singleChip)
    {
        chipList.push_back(singleChip);
    }
    return chipList;
}

std::shared_ptr<SmartIDReaderCardAdapter>
SmartIDReaderUnit::getDefaultSmartIDReaderCardAdapter()
{
    std::shared_ptr<ReaderCardAdapter> adapter = getDefaultReaderCardAdapter();
    return std::dynamic_pointer_cast<SmartIDReaderCardAdapter>(adapter);
}

std::string SmartIDReaderUnit::getReaderSerialNumber()
{
    std::string ret;

    return ret;
}

bool SmartIDReaderUnit::isConnected()
{
    return bool(d_insertedChip);
}

bool SmartIDReaderUnit::connectToReader()
{
    LOG(LogLevel::INFOS) << "Starting connection to reader...";
    std::shared_ptr<DataTransport> dataTransport = getDataTransport();
    if (!dataTransport->getReaderUnit())
    {
        dataTransport->setReaderUnit(shared_from_this());
        setDataTransport(dataTransport);
    }
    return getDataTransport()->connect();
}

void SmartIDReaderUnit::disconnectFromReader()
{
    getDataTransport()->disconnect();
}

ByteVector SmartIDReaderUnit::getPingCommand() const
{
    ByteVector cmd;

    cmd.push_back(static_cast<unsigned char>(0x4f));

    return cmd;
}

std::string SmartIDReaderUnit::getInformation()
{
    return BufferHelper::getStdString(
        getDefaultSmartIDReaderCardAdapter()->sendCommand(0x4F, ByteVector()));
}

std::string SmartIDReaderUnit::getFirmwareVersion()
{
    ByteVector data;
    data.push_back(static_cast<unsigned char>(0x00));

    return BufferHelper::getStdString(
        getDefaultSmartIDReaderCardAdapter()->sendCommand(0x4F, data));
}

void SmartIDReaderUnit::reboot()
{
    getDefaultSmartIDReaderCardAdapter()->sendCommand(0xE0, ByteVector());
}

void SmartIDReaderUnit::resetRF(int offtime)
{
    ByteVector data;
    data.push_back(static_cast<unsigned char>(0x00));
    data.push_back(static_cast<unsigned char>(offtime));

    getDefaultSmartIDReaderCardAdapter()->sendCommand(0x4E, data, 1000 + offtime);
}

void SmartIDReaderUnit::serialize(boost::property_tree::ptree &parentNode)
{
    boost::property_tree::ptree node;
    ReaderUnit::serialize(node);
    parentNode.add_child(getDefaultXmlNodeName(), node);
}

void SmartIDReaderUnit::unSerialize(boost::property_tree::ptree &node)
{
    ReaderUnit::unSerialize(node);
}

std::shared_ptr<SmartIDReaderProvider> SmartIDReaderUnit::getSmartIDReaderProvider() const
{
    return std::dynamic_pointer_cast<SmartIDReaderProvider>(getReaderProvider());
}
}