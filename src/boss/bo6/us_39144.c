// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern AnimationFrame ric_anim_stand[];
extern AnimationFrame D_us_80182038[];
extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182050[];
extern AnimationFrame D_us_80182058[];

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

s32 BO6_RicCheckFacing(void) {
    if (g_Ric.unk44 & 2) {
        return 0;
    }

    if (RIC.facingLeft == 1) {
        if (g_Ric.padPressed & PAD_RIGHT) {
            RIC.facingLeft = 0;
            g_Ric.unk4C = 1;
            return -1;
        } else if (g_Ric.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Ric.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Ric.padPressed & PAD_LEFT) {
            RIC.facingLeft = 1;
            g_Ric.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

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

void BO6_RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames) {
    if (!kind) {
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_CRASH_DAGGER, 0x15), 0);
        if (g_Ric.timers[PL_T_INVINCIBLE_SCENE] <= invincibilityFrames) {
            g_Ric.timers[PL_T_INVINCIBLE_SCENE] = invincibilityFrames;
        }
    } else if (g_Ric.timers[PL_T_INVINCIBLE] <= invincibilityFrames) {
        g_Ric.timers[PL_T_INVINCIBLE] = invincibilityFrames;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_DisableAfterImage);

void func_us_801B9C14(void) {
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.disableFlag =
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.resetFlag =
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.index =
                g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].ext.afterImage.timer =
                    0;
}

void func_us_801B9C3C(void) { BO6_RicSetStep(PL_S_DEBUG); }

void BO6_RicSetCrouch(s32 kind, s32 velocityX) {
    BO6_RicSetStep(PL_S_CROUCH);
    BO6_RicSetAnimation(D_us_80182048);
    RIC.velocityX = velocityX;
    RIC.velocityY = 0;
    if (kind == 1) {
        RIC.anim = D_us_80182038;
        RIC.step_s = 4;
    }
    if (kind == 2) {
        RIC.anim = D_us_80182058;
        RIC.step_s = 1;
    }
    if (kind == 3) {
        RIC.anim = D_us_80182050;
        RIC.step_s = 4;
    }
}

void BO6_RicSetStand(s32 velocityX) {
    RIC.velocityX = velocityX;
    RIC.velocityY = 0;
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_STAND);
    BO6_RicSetAnimation(ric_anim_stand);
}

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

Entity* BO6_RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* BO6_RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

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
