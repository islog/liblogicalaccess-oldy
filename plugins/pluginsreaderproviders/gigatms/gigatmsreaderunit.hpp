/**
 * \file gigatmsreaderunit.hpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief GIGA-TMS Reader unit.
 */

#ifndef LOGICALACCESS_GIGATMSREADERUNIT_HPP
#define LOGICALACCESS_GIGATMSREADERUNIT_HPP

#include <logicalaccess/readerproviders/readerunit.hpp>
#include <logicalaccess/plugins/readers/gigatms/gigatmsreaderunitconfiguration.hpp>
#include <logicalaccess/plugins/readers/gigatms/lla_readers_gigatms_api.hpp>

namespace logicalaccess
{
class Profile;
class GigaTMSReaderCardAdapter;
class GigaTMSReaderProvider;

/**
 * \brief The GIGA-TMS reader unit class.
 */
class LLA_READERS_GIGATMS_API GigaTMSReaderUnit : public ReaderUnit
{
  public:
    /**
     * \brief Constructor.
     */
    GigaTMSReaderUnit();

    /**
     * \brief Destructor.
     */
    virtual ~GigaTMSReaderUnit();

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
     * \brief Set the reader communication protocol.
     */
    void setCommunicationProtocol();

    /**
     * \brief Get the current chip in air.
     * \return The chip in air.
     */
    std::shared_ptr<Chip> getChipInAir();

    /**
     * \brief Connect to the card.
     * \return True if the card was connected without error, false otherwise.
     *
     * If the card handle was already connected, connect() first call disconnect(). If you
     * intend to do a reconnection, call reconnect() instead.
     */
    bool connect() override;

    /**
     * \brief Disconnect from the reader.
     * \see connect
     *
     * Calling this method on a disconnected reader has no effect.
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
     * \brief Serialize the current object to XML.
     * \param parentNode The parent node.
     */
    void serialize(boost::property_tree::ptree &parentNode) override;

    /**
     * \brief UnSerialize a XML node to the current object.
     * \param node The XML node.
     */
    void unSerialize(boost::property_tree::ptree &node) override;

    std::shared_ptr<GigaTMSReaderCardAdapter> getDefaultGigaTMSReaderCardAdapter();

    /**
     * \brief Get the GIGA-TMS reader unit configuration.
     * \return The GIGA-TMS reader unit configuration.
     */
    std::shared_ptr<GigaTMSReaderUnitConfiguration> getGigaTMSConfiguration()
    {
        return std::dynamic_pointer_cast<GigaTMSReaderUnitConfiguration>(
            getConfiguration());
    }

    /**
     * \brief Get the GIGA-TMS reader provider.
     * \return The GIGA-TMS reader provider.
     */
    std::shared_ptr<GigaTMSReaderProvider> getGigaTMSReaderProvider() const;
};
}

#endif