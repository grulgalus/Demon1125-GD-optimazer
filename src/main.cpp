#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

bool g_hasBeenWelcomed = false;

// 1. VIP UVÍTÁNÍ
class $modify(DemonMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        if (!g_hasBeenWelcomed && Mod::get()->getSettingValue<bool>("show-welcome")) {
            auto accountManager = GJAccountManager::sharedState();
            std::string currentUsername = accountManager->m_username;

            if (currentUsername == "demon1125") {
                FLAlertLayer::create("Demon1125 Optimizer", "Vítej zpět v GD, mistře <cg>demon1125</c>!\nModernFix engine je aktivní.", "Jdeme hrát!")->show();
            } else {
                FLAlertLayer::create("Demon1125 Optimizer", "Optimizer (ModernFix verze) úspěšně načten.\n<cr>(Vytvořil demon1125)</c>", "OK")->show();
            }
            g_hasBeenWelcomed = true;
        }
        return true;
    }
};

// 2. RAM A AUTO-LDM OPTIMALIZACE
class $modify(DemonPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (Mod::get()->getSettingValue<bool>("force-ldm") && level->m_objectCount > 15000) {
            level->m_lowDetailModeToggled = true;
        }

        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        if (Mod::get()->getSettingValue<bool>("clear-ram")) {
            CCDirector::get()->getTextureCache()->removeUnusedTextures();
            log::info("[Demon1125 Optimizer] RAM pročištěna!");
        }
        return true;
    }

    // 3. VYPNOUT KAMERA SHAKE (Ušetří výkon enginu)
    void shakeCamera(float p0, float p1, float p2) {
        if (Mod::get()->getSettingValue<bool>("disable-shake")) {
            return; // Zablokuje otřes kamery úplně
        }
        PlayLayer::shakeCamera(p0, p1, p2);
    }
};

// 4. INSTANT RESPAWN (Odstranění lagů při smrti)
class $modify(DemonPlayerObject, PlayerObject) {
    void playDeathEffect() {
        if (Mod::get()->getSettingValue<bool>("no-death-effect")) {
            // Úplně přeskočíme kód, který tvoří ty lagující částice!
            // Neuděláme nic, hráč prostě okamžitě zmizí a začne nový pokus.
            this->setVisible(false);
            return; 
        }
        PlayerObject::playDeathEffect();
    }
};
