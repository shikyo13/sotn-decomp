// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9144);

void func_us_801B9338(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9340);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B94CC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B96F4);

void BO6_RicSetStep(s16 step) {
    RIC.step = step;
    RIC.step_s = 0;
}

void BO6_RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
}

void DecelerateX(s32 speed) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

void DecelerateY(s32 arg0)
{
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0 = g_CurrentEntity->velocityY;
    if (temp_v0 < 0) {
        temp_v0_2 = arg0 + temp_v0;
        g_CurrentEntity->velocityY = temp_v0_2;
        if (temp_v0_2 > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        temp_v0_3 = temp_v0 - arg0;
        g_CurrentEntity->velocityY = temp_v0_3;
        if (temp_v0_3 < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckFacing);

void BO6_RicSetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1)
        speed = -speed;
    g_CurrentEntity->velocityX = speed;
}

void func_us_801B9ACC(s32 speed) {
    if (RIC.entityRoomIndex == 1)
        speed = -speed;
    RIC.velocityX = speed;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetInvincibilityFrames);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DisableAfterImage);

void func_us_801B9C14(void) {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.timer =
                    0;
}

void func_us_801B9C3C(void) { BO6_RicSetStep(PL_S_DEBUG); }

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetCrouch);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetStand);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9D74);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9DE4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801B9E70);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetFall);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA050);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckSubwpnChainLimit);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoSubweapon);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoAttack);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoCrash);

void BO6_RicSetDeadPrologue(void) { BO6_RicSetStep(PL_S_DEAD_PROLOGUE); }

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicSetSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BA9D0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckInput);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicGetFreeEntity);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicGetFreeEntityReverse);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB314);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB370);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckSubweapon);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BB5BC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByHoly);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByDark);

void func_us_801BBBC0(void) {}

void func_us_801BBBC8(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BBBD0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCreateEntFactoryFromEntity);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityFactory);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC2F0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC3E0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC4F8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC5C8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD384);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD47C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityPlayerBlinkWhite);
