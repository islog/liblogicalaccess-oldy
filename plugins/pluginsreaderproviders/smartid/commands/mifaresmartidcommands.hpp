/**
 * \file mifaresmartidcommands.hpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief Mifare SmartID card.
 */

#ifndef LOGICALACCESS_MIFARESMARTIDCOMMANDS_HPP
#define LOGICALACCESS_MIFARESMARTIDCOMMANDS_HPP

#include <logicalaccess/plugins/cards/mifare/mifarecommands.hpp>
#include <logicalaccess/plugins/readers/smartid/readercardadapters/mifaresmartidreadercardadapter.hpp>

#include <string>
#include <vector>
#include <iostream>

namespace logicalaccess
{
#define CMD_MIFARESMARTID "MifareSmartID"
/**
 * \brief The Mifare commands class for SmartID reader.
 */
class LLA_READERS_SMARTID_API MifareSmartIDCommands : public MifareCommands
{
  public:
    /**
     * \brief Constructor.
     */
    MifareSmartIDCommands();

    explicit MifareSmartIDCommands(std::string);

    /**
     * \brief Destructor.
     */
    virtual ~MifareSmartIDCommands();

    /**
     * \brief Get the SmartID reader/card adapter.
     * \return The SmartID reader/card adapter.
     */
    std::shared_ptr<MifareSmartIDReaderCardAdapter>
    getMifareSmartIDReaderCardAdapter() const
    {
        return std::dynamic_pointer_cast<MifareSmartIDReaderCardAdapter>(
            getReaderCardAdapter());
    }

    /**
     * \brief Load a key on a given location.
     * \param location The location.
     * \param key The key.
     * \param keytype The mifare key type.
     */
    void loadKey(std::shared_ptr<Location> location, MifareKeyType keytype,
                 std::shared_ptr<MifareKey> key) override;

    /**
     * \brief Authenticate a block, given a key number.
     * \param blockno The block number.
     * \param key_storage The key storage used for authentication.
     * \param keytype The key type.
     */
    void authenticate(unsigned char blockno, std::shared_ptr<KeyStorage> key_storage,
                      MifareKeyType keytype) override;

    /**
     * \brief Load a key to the reader.
     * \param keyno The key number.
     * \param keytype The key type.
     * \param key The key.
     * \param vol Use volatile memory.
     * \return true on success, false otherwise.
     */
    bool loadKey(unsigned char keyno, MifareKeyType keytype,
                 std::shared_ptr<MifareKey> key, bool vol = false) override;
    /**
     * \brief Authenticate a block, given a key number.
     * \param blockno The block number.
     * \param keyno The key number, previously loaded with Mifare::loadKey().
     * \param keytype The key type.
     */
    void authenticate(unsigned char blockno, unsigned char keyno,
                      MifareKeyType keytype) override;

    /**
     * \brief Read bytes from the card.
     * \param blockno The block number.
     * \param len The count of bytes to read. (0 <= len < 16)
     * \param buf The buffer in which to place the data.
     * \param buflen The length of buffer.
     * \return The count of bytes red.
     */
    ByteVector readBinary(unsigned char blockno, size_t len) override;

    /**
     * \brief Write bytes to the card.
     * \param blockno The block number.
     * \param buf The buffer containing the data.
     * \param buflen The length of buffer.
     * \return The count of bytes written.
     */
    void updateBinary(unsigned char blockno, const ByteVector &buf) override;

    /**
    * \brief Increment a block value.
    * \param blockno The block number.
    * \param value The increment value.
    *
    * @note This internally call transfer ! Use increment_raw() if you wish to perform
    * transfer() yourself.
    */
    void increment(unsigned char blockno, uint32_t value) override;

    /**
    * \brief Decrement a block value.
    * \param blockno The block number.
    * \param value The decrement value.
    *
    * @note This internally call transfer ! Use decrement_raw() if you wish to perform
    * transfer() yourself.
    */
    void decrement(unsigned char blockno, uint32_t value) override;

    /**
     * Send the Increment Mifare command but doesn't not automatically perform
     * a transfer.
     */
    void increment_raw(uint8_t blockno, uint32_t value) const;

    /**
     * Send the Decrement Mifare command but doesn't not automatically perform
     * a transfer.
     */
    void decrement_raw(uint8_t blockno, uint32_t value) const;

    /**
    * \brief Transfer volatile memory to block value.
    * \param blockno The block number.
    */
    virtual void transfer(unsigned char blockno);

    /**
    * \brief Store block value to volatile memory.
    * \param blockno The block number.
    */
    virtual void restore(unsigned char blockno);
};
}

#endif /* LOGICALACCESS_MIFARESMARTIDCARDPROVIDER_HPP */