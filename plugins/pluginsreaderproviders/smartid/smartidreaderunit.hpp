/**
 * \file smartidreaderunit.hpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief SmartID Reader unit.
 */

#ifndef LOGICALACCESS_SMARTIDREADERUNIT_HPP
#define LOGICALACCESS_SMARTIDREADERUNIT_HPP

#include <logicalaccess/readerproviders/readerunit.hpp>
#include <logicalaccess/plugins/readers/smartid/smartidreaderunitconfiguration.hpp>
#include <logicalaccess/cards/chip.hpp>
#include <logicalaccess/plugins/readers/smartid/lla_readers_smartid_api.hpp>

namespace logicalaccess
{
class Profile;
class SmartIDReaderCardAdapter;
class ReaderCommunication;
class MifareSmartIDCardProvider;
class SmartIDReaderProvider;

/**
 * \brief The SmartID reader unit class.
 */
class LLA_READERS_SMARTID_API SmartIDReaderUnit : public ReaderUnit
{
  public:
    /**
     * \brief Constructor.
     */
    SmartIDReaderUnit();

    /**
     * \brief Destructor.
     */
    virtual ~SmartIDReaderUnit();

    /**
     * \brief Get the reader unit name.
     * \return The reader unit name.
     */
    std::string getName() const override;

    /**
     * \brief Get the connected reader unit name.
     * \return The connected reader unit name.
     */
    std::string getConnectedName() override;

    /**
     * \brief Set the card type.
     * \param cardType The card type.
     */
    void setCardType(std::string cardType) override;

    /**
     * \brief Get the reader communication for a card type.
     * \param cardType The card type.
     * \return The reader communication
     */
    static std::shared_ptr<ReaderCommunication>
    getReaderCommunication(std::string cardType);

    /**
     * \brief Wait for a card insertion.
     * \param maxwait The maximum time to wait for, in milliseconds. If maxwait is zero,
     * then the call never times out.
     * \return True if a card was inserted, false otherwise. If a card was inserted, the
     * name of the reader on which the insertion was detected is accessible with
     * getReader().
     * \warning If the card is already connected, then the method always fail.
     */
    bool waitInsertion(unsigned int maxwait) override;

    /**
     * \brief Wait for a card removal.
     * \param maxwait The maximum time to wait for, in milliseconds. If maxwait is zero,
     * then the call never times out.
     * \return True if a card was removed, false otherwise. If a card was removed, the
     * name of the reader on which the removal was detected is accessible with
     * getReader().
     */
    bool waitRemoval(unsigned int maxwait) override;

    /**
     * \brief Create the chip object from card type.
     * \param type The card type.
     * \return The chip.
     */
    std::shared_ptr<Chip> createChip(std::string type) override;

    /**
     * \brief Get the first and/or most accurate chip found.
     * \return The single chip.
     */
    std::shared_ptr<Chip> getSingleChip() override;

    /**
     * \brief Get chip available in the RFID rang.
     * \return The chip list.
     */
    std::vector<std::shared_ptr<Chip>> getChipList() override;

    /**
     * \brief Get the reader ping command.
     * \return The ping command.
     */
    ByteVector getPingCommand() const override;

    /**
     * \brief Get the card serial number.
     * \return The card serial number.
     */
    ByteVector getCardSerialNumber();

    /**
     * \brief Get the default SmartID reader/card adapter.
     * \return The default SmartID reader/card adapter.
     */
    virtual std::shared_ptr<SmartIDReaderCardAdapter>
    getDefaultSmartIDReaderCardAdapter();

    /**
     * \brief Connect to the card.
     * \return True if the card was connected without error, false otherwise.
     *
     * If the card handle was already connected, connect() first call disconnect(). If you
     * intend to do a reconnection, call reconnect() instead.
     */
    bool connect() override;

    /**
     * \brief Disconnect from the SmartID.
     * \see connect
     *
     * Calling this method on a disconnected SmartID has no effect.
     */
    void disconnect() override;

    /**
     * \brief Check if the card is connected.
     * \return True if the card is connected, false otherwise.
     */
    bool isConnected() override;

    /**
     * \brief Connect to the reader. Implicit connection on first command sent.
     * \return True if the connection successed.
     */
    bool connectToReader() override;

    /**
     * \brief Disconnect from reader.
     */
    void disconnectFromReader() override;

    /**
     * \brief Get a string hexadecimal representation of the reader serial number
     * \return The reader serial number or an empty string on error.
     */
    std::string getReaderSerialNumber() override;

    /**
     * \brief Get information about the SmartID.
     * \return A string describing the SmartID.
     */
    std::string getInformation();

    /**
     * \brief Get information about the SmartID's firmware.
     * \return A string describing the SmartID's firmware.
     */
    std::string getFirmwareVersion();

    /**
     * \brief Reboot the SmartID.
     */
    void reboot();

    /**
     * \brief Reset the RF field.
     * \param offtime The offtime, in milliseconds. Default is 100.
     */
    void resetRF(int offtime = 100);

    /**
     * \brief Serialize the current object to XML.
     * \param parentNode The parent node.
     */
    void serialize(boost::property_tree::ptree &parentNode) override;

    /**
     * \brief UnSerialize a XML node to the current object.
     * \param node The XML node.
     */
    void unSerialize(boost::property_tree::ptree &node) override;

    /**
     * \brief Get the SmartID reader unit configuration.
     * \return The SmartID reader unit configuration.
     */
    std::shared_ptr<SmartIDReaderUnitConfiguration> getSmartIDConfiguration()
    {
        return std::dynamic_pointer_cast<SmartIDReaderUnitConfiguration>(
            getConfiguration());
    }

    /**
     * \brief Get the SmartID reader provider.
     * \return The SmartID reader provider.
     */
    std::shared_ptr<SmartIDReaderProvider> getSmartIDReaderProvider() const;

  protected:
    /**
     * \brief The reader communication.
     */
    std::shared_ptr<ReaderCommunication> d_readerCommunication;
};
}

#endif