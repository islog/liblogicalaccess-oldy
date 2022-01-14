/**
 * \file generictagidondemandchip.hpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief Generic tag IdOnDemand chip.
 */

#ifndef LOGICALACCESS_GENERICTAGIDONDEMANDCHIP_HPP
#define LOGICALACCESS_GENERICTAGIDONDEMANDCHIP_HPP

#include <logicalaccess/plugins/cards/generictag/generictagchip.hpp>
#include <logicalaccess/plugins/readers/idondemand/lla_readers_idondemand_api.hpp>

namespace logicalaccess
{
/**
 * \brief The Generic Tag IdOnDemand commands class.
 */
class LLA_READERS_IDONDEMAND_API GenericTagIdOnDemandChip : public GenericTagChip
{
  public:
    /**
     * \brief Constructor.
     */
    GenericTagIdOnDemandChip();

    /**
     * \brief Destructor.
     */
    ~GenericTagIdOnDemandChip();

    /**
     * \brief Get a card service for this card provider.
     * \param serviceType The card service type.
     * \return The card service.
     */
    std::shared_ptr<CardService> getService(CardServiceType serviceType) override;
};
}

#endif