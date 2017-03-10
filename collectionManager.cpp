#include <vector>
#include <string>
#include "collectionManager.h"

namespace cm {

    std::vector<card> collection;
    void addCard(std::string cardName, std::string cardID, std::string cardClass) {
        struct card newCard;
        newCard.name = cardName;
        newCard.id = cardID;
        newCard.className = cardClass;
        collection.push_back(newCard);
    }

    //druid, hunter(63), mage, pally, priest, rogue, shaman, wl, war, neutral
    void fillSearchCollection() {
        //DRUID (61)
        addCard("Innervate","EX1_169","DRUID");
        addCard("Moonfire","CS2_008","DRUID");
        addCard("Claw","CS2_005","DRUID");
        addCard("Enchanted Raven","KAR_300","DRUID");
        addCard("Forbidden Ancient","OG_051","DRUID");
        addCard("Jade Idol","CFM_602","DRUID");
        addCard("Living Roots","AT_037","DRUID");
        addCard("Mark of the Lotus","CFM_614","DRUID");
        addCard("Naturalize","EX1_161","DRUID");
        addCard("Raven Idol","LOE_115","DRUID");
        addCard("Savagery","EX1_578","DRUID");
        addCard("Darnassus Aspirant","AT_038","DRUID");
        addCard("Druid of the Saber","AT_042","DRUID");
        addCard("Mark of the Wild","CS2_009","DRUID");
        addCard("Mark of Y'Shaarj","OG_048","DRUID");
        addCard("Power of the Wild","EX1_160","DRUID");
        addCard("Wild Growth","CS2_013","DRUID");
        addCard("Wrath","EX1_154","DRUID");
        addCard("Addled Grizzly","OG_313","DRUID");
        addCard("Celestial Dreamer","CFM_617","DRUID");
        addCard("Druid of the Flame","BRM_010","DRUID");
        addCard("Feral Rage","OG_047","DRUID");
        addCard("Healing Touch","CS2_007","DRUID");
        addCard("Jade Blossom","CFM_713","DRUID");
        addCard("Mark of Nature","EX1_155","DRUID");
        addCard("Mounted Raptor","LOE_050","DRUID");
        addCard("Mulch","AT_044","DRUID");
        addCard("Pilfered Power","CFM_616","DRUID");
        addCard("Savage Roar","CS2_011","DRUID");
        addCard("Astral Communion","AT_043","DRUID");
        addCard("Bite","EX1_570","DRUID");
        addCard("Fandral Staghelm","OG_044","DRUID");
        addCard("Jungle Moonkin","LOE_051","DRUID");
        addCard("Keeper of the Grove","EX1_166","DRUID");
        addCard("Klaxxi Amber-Weaver","OG_188","DRUID");
        addCard("Mire Keeper","OG_202","DRUID");
        addCard("Savage Combatant","AT_039","DRUID");
        addCard("Soul of the Forest","EX1_158","DRUID");
        addCard("Swipe","CS2_012","DRUID");
        addCard("Wildwalker","AT_040","DRUID");
        addCard("Druid of the Claw","EX1_165","DRUID");
        addCard("Force of Nature","EX1_571","DRUID");
        addCard("Lunar Visions","CFM_811","DRUID");
        addCard("Nourish","EX1_164","DRUID");
        addCard("Starfall","NEW1_007","DRUID");
        addCard("Virmen Sensei","CFM_816","DRUID");
        addCard("Dark Arakkoa","OG_293","DRUID");
        addCard("Jade Behemoth","CFM_343","DRUID");
        addCard("Menagerie Warden","KAR_065","DRUID");
        addCard("Moonglade Portal","KAR_075","DRUID");
        addCard("Starfire","EX1_173","DRUID");
        addCard("Ancient of Lore","NEW1_008","DRUID");
        addCard("Ancient of War","EX1_178","DRUID");
        addCard("Knight of the Wild","AT_041","DRUID");
        addCard("Wisps of the Old Gods","OG_195","DRUID");
        addCard("Ironbark Protector","CS2_232","DRUID");
        addCard("Aviana","AT_045","DRUID");
        addCard("Cenarius","EX1_573","DRUID");
        addCard("Volcanic Lumberer","BRM_009","DRUID");
        addCard("Kun the Forgotten King","CFM_308","DRUID");

        //
    }
}

