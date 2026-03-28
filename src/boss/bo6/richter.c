// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s32 D_us_801CF3C8;
extern s32 D_us_801CF3CC;
extern AnimationFrame D_us_801820B0[];
extern s32 D_us_801D07F8;
extern AnimationFrame D_us_80181F24[];
extern EInit D_us_80180400;
extern s16 D_us_801D1686;
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;
extern AnimationFrame D_us_80181F1C[];
extern AnimationFrame D_us_80182130[];
extern AnimationFrame D_us_801822B8[];
extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182068[];
extern AnimationFrame D_us_80182110[];
extern AnimationFrame D_us_801822C0[];
extern AnimationFrame D_us_801820E4[];
extern AnimationFrame D_us_801822C8[];
extern AnimationFrame D_us_8018224C[];
extern AnimationFrame D_us_80182224[];
extern AnimationFrame D_us_8018228C[];
extern AnimationFrame D_us_8018221C[];
extern s32 D_us_80181278;
extern s32 D_us_801D11C0;

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4BD0);

void func_us_801B4EAC(void) {
    g_Ric.unk04 = g_Ric.vram_flag;
    g_Ric.vram_flag = 0;
    RIC.posY.val += RIC.velocityY;
    RIC.posX.val += RIC.velocityX;
    if (RIC.posY.val < (s32)0xB30000) {
        RIC.posY.val = 0xB30000;
        g_Ric.vram_flag = TOUCHING_GROUND;
    }
    if (RIC.posY.val > 0x280000) {
        RIC.posY.val = 0x280000;
        g_Ric.vram_flag |= TOUCHING_CEILING;
    }
    if (RIC.posX.val > (s32)0xF80000) {
        RIC.posX.val = 0xF80000;
        g_Ric.vram_flag |= TOUCHING_R_WALL;
    }
    if (RIC.posX.val < 0x80000) {
        RIC.posX.val = 0x80000;
        g_Ric.vram_flag |= TOUCHING_L_WALL;
    }
}

void BO6_CheckBladeDashInput(void) {
    if (RIC.step == PL_S_STAND || RIC.step == PL_S_WALK ||
        RIC.step == PL_S_CROUCH || RIC.step == PL_S_FALL ||
        RIC.step == PL_S_JUMP) {
        if (!g_Ric.unk46 && (g_Ric.padTapped & 8)) {
            func_us_801BA9D0();
        }
    }
}

void BO6_CheckHighJumpInput(void) {
    s32 valid = 0;

    if (RIC.step == PL_S_CROUCH || RIC.step == PL_S_STAND) {
        valid = 1;
    }
    if (RIC.step == PL_S_JUMP && RIC.velocityY > 0x10000) {
        valid = 1;
    }
    if (RIC.step == PL_S_FALL) {
        valid = 1;
    }
    if (valid && !g_Ric.unk46 && (g_Ric.padTapped & 2)) {
        func_us_801BA050();
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicMain);

void func_us_801B5A14(s32 arg0) {
    D_us_801CF3C8 = arg0;
    D_us_801CF3CC = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", RichterThinking);

void func_us_801B6998(void) {
    s32 timer = D_us_80181278;

    switch (timer) {
    case 0x0A:
        if (g_CastleFlags[0x95] != 0) {
            break;
        }
        if (g_DemoMode) {
            break;
        }
        g_unkGraphicsStruct.g_zEntityCenter = 1;
        D_us_801D11C0 = 0;
        break;
    case 0x0B:
        D_us_801D11C0++;
        if (D_us_801D11C0 < 2) {
            return;
        }
        if (g_CastleFlags[0x95] != 0) {
            break;
        }
        if (g_DemoMode) {
            break;
        }
        g_unkGraphicsStruct.unk20 = 0xFF;
        break;
    case 0x14:
        if (!(g_CutsceneFlags & 4)) {
            return;
        }
        D_us_80181278 = 0x1E;
        return;
    case 0x28:
        g_CutsceneFlags |= 8;
        return;
    default:
        return;
    }
    D_us_80181278++;
}

void EntityRichter(Entity* self) {
    Entity* entity;
    s16 i;

    g_Ric.unk6A = RIC.hitPoints;
    if (self->step == 0) {
        InitializeEntity(&D_us_80180400);
        func_us_801B4BD0();
        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = STAGE_ENTITY_START + 4; i < 0x90; i++, entity++) {
            DestroyEntity(entity);
        }
        D_us_801D1686 = RIC.hitPoints;
        D_us_801CF3E0 = 0;
        g_Ric.unk6C = RIC.hitPoints;
        g_Ric.unk6A = RIC.hitPoints;
        g_Ric.unk70 = RIC.hitboxState;
        D_us_801CF3E4 = (u16)D_us_801D1686 >> 1;
        func_us_801B5A14(0x12);
        BO6_DisableAfterImage(1, 0x30);
    } else {
        RichterThinking();
        BO6_RicMain();
        func_us_801BBBD0();
        func_us_801B6998();
    }
    g_Ric.unk6C = g_Ric.unk6A;
}

void BO6_RicStepStand(void) {
    if (BO6_RicCheckInput(0x4305C)) {
        return;
    }
    DecelerateX(0x2000);
    switch (RIC.step_s) {
    case 0:
        if (BO6_RicCheckFacing()) {
            func_us_801B9DE4(0);
        } else if (g_Ric.padPressed & PAD_UP) {
            BO6_RicSetAnimation(D_us_80181F1C);
            RIC.step_s = 1;
            break;
        }
        break;
    case 1:
        if (BO6_RicCheckFacing()) {
            func_us_801B9DE4(0);
        } else if (g_Ric.padPressed & PAD_UP) {
        } else {
            BO6_RicSetStand(0);
        }
        break;
    case 0x40:
        BO6_DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            BO6_RicCheckFacing();
            if (g_Ric.padPressed & PAD_DOWN) {
                RIC.step = PL_S_CROUCH;
                RIC.anim = D_us_80182130;
                break;
            }
        }

        if (RIC.poseTimer < 0) {
            if (g_Ric.padPressed & PAD_SQUARE) {
                RIC.step_s++;
                g_Ric.unk46 = 2;
                BO6_RicSetAnimation(D_us_801822B8);
                BO6_RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                break;
            }
            g_Ric.unk46 = 0;
            BO6_RicSetStand(0);
        }
        break;
    case 0x41:
        BO6_DisableAfterImage(1, 1);
        if (g_Ric.padPressed & PAD_SQUARE) {
            break;
        }
        g_Ric.unk46 = 0;
        BO6_RicSetStand(0);
        break;
    case 0x42:
        BO6_DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            BO6_RicCheckFacing();
        }
        if (RIC.poseTimer < 0) {
            g_Ric.unk46 = 0;
            BO6_RicSetStand(0);
        }
        break;
    }
}

void BO6_RicStepWalk(void) {
    if (BO6_RicCheckInput(0x305C)) {
        return;
    }
    DecelerateX(0x2000);
    if (!BO6_RicCheckFacing()) {
        BO6_RicSetStand(0);
        return;
    }
    if (!RIC.step_s) {
        BO6_RicSetSpeedX(0x14000);
    }
}

void BO6_RicStepRun(void) {
    g_Ric.timers[PL_T_8] = 8;
    g_Ric.timers[PL_T_CURSE] = 8;
    if (BO6_RicCheckInput(0x305C)) {
        return;
    }
    DecelerateX(0x2000);
    if (!BO6_RicCheckFacing()) {
        BO6_RicSetStand(0);
        if (g_Ric.timers[PL_T_RUN]) {
            RIC.velocityX = 0;
            return;
        }
        if (g_Ric.vram_flag & 0xC) {
            return;
        }
        BO6_RicSetAnimation(D_us_80181F24);
        BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        return;
    }
    if (!RIC.step_s) {
        BO6_RicSetSpeedX(0x24000);
    }
}

void BO6_RicStepJump(void) {
    s32 facing;

    if ((g_Ric.vram_flag & TOUCHING_CEILING) &&
        (RIC.velocityY < -0x10000)) {
        RIC.velocityY = -0x4000;
        g_Ric.unk44 |= 0x20;
    }
    if (BO6_RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_JUMP)) {
        return;
    }
    switch (RIC.step_s) {
    case 0:
        DecelerateX(0x1000);
        facing = BO6_RicCheckFacing();
        if (facing) {
            if (g_Ric.unk44 & 0x10) {
                BO6_RicSetSpeedX(0x24000);
            } else {
                BO6_RicSetSpeedX(0x14000);
            }
            g_Ric.unk44 &= ~4;
        } else {
            g_Ric.unk44 &= ~0x10;
            if ((RIC.pose < 2) && !(g_Ric.unk44 & 8) &&
                (g_Ric.unk44 & 4) && (g_Ric.padTapped & PAD_CROSS)) {
                BO6_RicSetAnimation(D_us_801820E4);
                BO6_RicSetSpeedX(0xFFFE8000);
                RIC.velocityY = (s32)0xFFFD6000;
                g_Ric.unk44 |= 0xA;
                g_Ric.unk44 &= ~4;
                RIC.step_s = 2;
            }
        }
        break;
    case 2:
        break;
    case 0x40:
        BO6_DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            facing = BO6_RicCheckFacing();
            if (facing) {
                if (g_Ric.unk44 & 0x10) {
                    BO6_RicSetSpeedX(0x24000);
                } else {
                    BO6_RicSetSpeedX(0x14000);
                }
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        } else {
            if (((g_Ric.padPressed & PAD_RIGHT) && RIC.facingLeft == 0) ||
                ((g_Ric.padPressed & PAD_LEFT) && RIC.facingLeft)) {
                if (g_Ric.unk44 & 0x10) {
                    BO6_RicSetSpeedX(0x24000);
                } else {
                    BO6_RicSetSpeedX(0x14000);
                }
                BO6_RicSetSpeedX(0x14000);
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.padPressed & PAD_SQUARE) {
                RIC.step_s += 1;
                g_Ric.unk46 = 2;
                BO6_RicSetAnimation(D_us_801822C8);
                BO6_RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
            }
        }
        break;
    case 0x41:
        BO6_DisableAfterImage(1, 1);
        if (!(g_Ric.padPressed & PAD_SQUARE)) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            BO6_RicSetAnimation(D_us_801820B0);
        }
        break;
    case 0x42:
        BO6_DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            facing = BO6_RicCheckFacing();
            if (facing) {
                if (g_Ric.unk44 & 0x10) {
                    BO6_RicSetSpeedX(0x24000);
                } else {
                    BO6_RicSetSpeedX(0x14000);
                }
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        } else {
            if (((g_Ric.padPressed & PAD_RIGHT) && RIC.facingLeft == 0) ||
                ((g_Ric.padPressed & PAD_LEFT) && RIC.facingLeft)) {
                if (g_Ric.unk44 & 0x10) {
                    BO6_RicSetSpeedX(0x24000);
                } else {
                    BO6_RicSetSpeedX(0x14000);
                }
                BO6_RicSetSpeedX(0x14000);
                g_Ric.unk44 &= ~4;
            } else {
                g_Ric.unk44 &= ~0x10;
            }
        }
        if (RIC.poseTimer < 0) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            BO6_RicSetAnimation(D_us_801820B0);
        }
        break;
    }
}

void BO6_RicStepFall(void) {
    if (BO6_RicCheckInput(0x9009)) {
        return;
    }
    DecelerateX(0x1000);
    if (RIC.step_s) {
        return;
    }
    if (g_Ric.timers[PL_T_5] && (g_Ric.padTapped & PAD_CROSS)) {
        func_us_801B9E70();
        return;
    }
    if (BO6_RicCheckFacing()) {
        BO6_RicSetSpeedX(0xC000);
    }
}

void BO6_RicStepCrouch(void) {
    if (BO6_RicCheckInput(0x4105C)) {
        return;
    }
    DecelerateX(0x2000);
    switch (RIC.step_s) {
    case 0:
        if (!(g_Ric.padPressed & PAD_DOWN)) {
            BO6_RicSetAnimation(D_us_80182068);
            RIC.step_s = 2;
            return;
        }
        break;
    case 1:
        if (!(g_Ric.padPressed & PAD_DOWN)) {
            if (BO6_RicCheckFacing()) {
                func_us_801B9DE4(0);
                return;
            }
            RIC.anim = D_us_80182068;
            RIC.step_s = 2;
            RIC.poseTimer = 1;
            RIC.pose = 2 - RIC.pose;
            break;
        }
    case 4:
        if (RIC.poseTimer != -1) {
            return;
        }
        BO6_RicSetAnimation(D_us_80182048);
        RIC.step_s = 0;
        break;
    case 2:
        if (BO6_RicCheckFacing()) {
            func_us_801B9DE4(0);
            return;
        }
        if (RIC.poseTimer == -1) {
            BO6_RicSetStand(0);
            return;
        }
        break;
    case 3:
        if (RIC.poseTimer < 0) {
            BO6_RicSetAnimation(D_us_80182048);
            RIC.step_s = 0;
            return;
        }
        break;
    case 0x40:
        BO6_DisableAfterImage(1, 1);
        if (RIC.pose < 3) {
            BO6_RicCheckFacing();
            if (!(g_Ric.padPressed & PAD_DOWN)) {
                RIC.step = PL_S_STAND;
                RIC.anim = D_us_80182110;
                return;
            }
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.padPressed & PAD_SQUARE) {
                RIC.step_s++;
                g_Ric.unk46 = 2;
                BO6_RicSetAnimation(D_us_801822C0);
                BO6_RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                return;
            }
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            BO6_RicSetAnimation(D_us_80182048);
        }
        break;
    case 0x41:
        BO6_DisableAfterImage(1, 1);
        if (!(g_Ric.padPressed & PAD_SQUARE)) {
            g_Ric.unk46 = 0;
            RIC.step_s = 0;
            BO6_RicSetAnimation(D_us_80182048);
        }
        break;
    }
}

void BO6_RicResetPose(void) {
    RIC.pose = RIC.poseTimer = 0;
    g_Ric.unk44 = 0;
    g_Ric.unk46 = 0;
    RIC.drawFlags &= ~ENTITY_ROTATE;
}

void func_us_801B77D8(void) {
    if (RIC.posX.i.hi - PLAYER.posX.i.hi <= 0) {
        RIC.entityRoomIndex = 0;
    } else {
        RIC.entityRoomIndex = 1;
    }
}

void BO6_RicStepHit(s32 damageEffect, u32 damageKind, s16 prevStep) {
    s16 prevStepIdx;

    switch (RIC.step_s) {
    case 0:
        BO6_RicResetPose();
        if (damageKind < 0x10) {
            func_us_801B77D8();
        } else {
            RIC.entityRoomIndex = RIC.facingLeft;
        }
        if (damageEffect & ELEMENT_THUNDER) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            RIC.velocityY = (s32)0xFFFC0000;
            func_us_801B9ACC(0xFFFEC000);
            RIC.step_s = 1;
            RIC.anim = D_us_8018224C;
            g_Ric.damagePalette = 0x8220;
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_THUNDER, 0);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x46), 0);
            g_Ric.timers[PL_T_2] = 6;
            g_api.PlaySfx(0x83B);
            return;
        }
        if (damageEffect & ELEMENT_ICE) {
            damageKind = 3;
        }
        switch (damageKind) {
        case 2:
            prevStepIdx = (s16)(prevStep - 1);
            if (prevStepIdx < 5) {
                switch (prevStepIdx) {
                case 0:
                case 1:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 6;
                    RIC.anim = D_us_80182224;
                    g_api.PlaySfx(0x837);
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    break;
                case 2:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 7;
                    RIC.anim = D_us_8018228C;
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(0x836);
                    break;
                case 3:
                case 4:
                    RIC.velocityY = (s32)0xFFFD0000;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(0x838);
                    break;
                }
            } else {
                goto default_prevstep;
            }
            break;
        default:
            prevStepIdx = (s16)(prevStep - 1);
        default_prevstep:
            if (prevStepIdx < 5) {
                switch (prevStepIdx) {
                case 0:
                case 1:
                    RIC.velocityY = (s32)0xFFFC0000;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(0x839);
                    break;
                case 2:
                    RIC.velocityY = 0;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 7;
                    RIC.anim = D_us_8018228C;
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    g_api.PlaySfx(0x83A);
                    break;
                case 3:
                case 4:
                    RIC.velocityY = (s32)0xFFFD0000;
                    func_us_801B9ACC(0xFFFEC000);
                    RIC.step_s = 1;
                    RIC.anim = D_us_8018221C;
                    g_api.PlaySfx(0x702);
                    g_api.PlaySfx(0x83A);
                    break;
                }
            } else {
                RIC.velocityY = (s32)0xFFFC0000;
                func_us_801B9ACC(0xFFFEC000);
                RIC.step_s = 1;
                RIC.anim = D_us_8018221C;
                g_api.PlaySfx(0x839);
            }
            break;
        }
        g_Ric.damagePalette = 0x8166;
        g_Ric.timers[PL_T_2] = 6;
        if (damageEffect & ELEMENT_FIRE) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_HIT_BY_FIRE, 1), 0);
            BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, 9, 0);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x43), 0);
            g_Ric.damagePalette = 0x8160;
            g_Ric.timers[PL_T_2] = 0x10;
            return;
        }
        if (damageEffect & ELEMENT_ICE) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_ICE, 0);
            g_Ric.timers[PL_T_2] = 0xC;
            g_Ric.damagePalette = 0x8169;
            return;
        }
        if (damageEffect & ELEMENT_DARK) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_DARK, 0);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x56), 0);
            g_Ric.timers[PL_T_2] = 0x10;
            g_Ric.damagePalette = 0x8164;
            return;
        }
        if (damageEffect & ELEMENT_HOLY) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_HIT_BY_HOLY, 0);
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x57), 0);
            g_Ric.timers[PL_T_2] = 8;
            g_Ric.damagePalette = 0x8168;
            return;
        }
        if (!(damageEffect & 0xF840)) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x53), 0);
        }
        return;
    case 1:
        if ((g_Ric.vram_flag & TOUCHING_CEILING) &&
            (RIC.velocityY < (s32)0xFFFF0000)) {
            RIC.velocityY = (s32)0xFFFF0000;
        }
        BO6_RicCheckInput(0x20280);
        return;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        DecelerateX(0x2000);
        if (!(g_Ric.vram_flag & TOUCHING_GROUND)) {
            BO6_RicSetFall();
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.unk5C) {
                if (g_Status.hp < 0x14) {
                    BO6_RicSetDeadPrologue();
                    return;
                }
            }
            BO6_RicSetStand(RIC.velocityX);
        }
        return;
    case 7:
        DecelerateX(0x2000);
        if (!(g_Ric.vram_flag & TOUCHING_GROUND)) {
            BO6_RicSetFall();
        }
        if (RIC.poseTimer < 0) {
            if (g_Ric.unk5C && g_Status.hp < 0x14) {
                BO6_RicSetDeadPrologue();
                return;
            }
            BO6_RicSetCrouch(0, RIC.velocityX);
        }
        return;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepDead);

void BO6_RicStepStandInAir(void) {
    if (!RIC.step_s) {
        RIC.velocityY += 0x3800;
        if (RIC.velocityY > 0) {
            RIC.velocityY = 0;
            RIC.step_s = 1;
        }
    } else if (g_Ric.unk4E) {
        g_Ric.unk46 = 0;
        BO6_RicSetStep(PL_S_JUMP);
        BO6_RicSetAnimation(D_us_801820B0);
        g_Ric.unk44 = 0;
    }
}

void BO6_RicStepEnableFlameWhip(void) {
    if (RIC.animCurFrame == 181 && RIC.poseTimer == 1) {
        BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_35, 0);
        g_api.PlaySfx(SFX_WEAPON_APPEAR);
    }

    if (RIC.poseTimer < 0) {
        BO6_RicSetStand(0);
        g_Ric.unk46 = 0;
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x45), 0);
        g_Ric.timers[PL_T_POISON] = 0x800;
    }
}

void BO6_RicStepHydrostorm(void) {
    if (RIC.poseTimer < 0) {
        BO6_RicSetStand(0);
        g_Ric.unk46 = 0;
    }
}

void BO6_RicStepGenericSubwpnCrash(void) {
    if (g_Ric.unk4E) {
        BO6_RicSetStand(0);
        g_Ric.unk46 = 0;
    }
}

void BO6_RicStepThrowDaggers(void) {
    if (!RIC.step_s) {
        D_us_801D07F8 = 0x200;
        RIC.step_s++;
    } else {
        BO6_RicCheckFacing();
        D_us_801D07F8--;
        if (!D_us_801D07F8) {
            g_Ric.unk46 = 0;
            BO6_RicSetStand(0);
            g_Ric.unk4E = 1;
        }
    }
    if (g_Ric.padTapped & PAD_CROSS) {
        func_us_801B9E70();
        g_Ric.unk46 = 0;
        g_Ric.unk4E = 1;
        D_us_801D07F8 = 0;
    }
}

void BO6_RicStepSlide(void) {
    s32 isTouchingGround = 0;

    if (RIC.facingLeft == 0 && g_Ric.vram_flag & TOUCHING_R_WALL) {
        isTouchingGround = 1;
    }
    if (RIC.facingLeft && g_Ric.vram_flag & TOUCHING_L_WALL) {
        isTouchingGround = 1;
    }
    if (RIC.posX.i.hi >= STAGE_WIDTH - 4 && RIC.facingLeft == 0) {
        isTouchingGround = 1;
    }
    if (RIC.posX.i.hi <= 4 && RIC.facingLeft) {
        isTouchingGround = 1;
    }
    if ((RIC.facingLeft == 0 &&
         g_Player.colFloor[2].effects & EFFECT_UNK_8000) ||
        (RIC.facingLeft && g_Player.colFloor[3].effects & EFFECT_UNK_8000)) {
        isTouchingGround = 1;
    }
    if (isTouchingGround && RIC.pose < 6) {
        RIC.pose = 6;
        if (RIC.velocityX > 0x10000) {
            RIC.velocityX = 0x20000;
        }
        if (RIC.velocityX < (s32)0xFFFF0000) {
            RIC.velocityX = (s32)0xFFFE0000;
        }
        BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
    }
    if (RIC.pose < 5) {
        if (BO6_RicCheckInput(CHECK_FALL | CHECK_CRASH)) {
            return;
        }
        if (g_Ric.padTapped & PAD_CROSS) {
            RIC.posY.i.hi -= 4;
            BO6_RicSetSlideKick();
            return;
        }
    } else if (RIC.pose < 7) {
        if (BO6_RicCheckInput(CHECK_SLIDE | CHECK_FALL | CHECK_CRASH)) {
            return;
        }
    } else if (BO6_RicCheckInput(
                   CHECK_SLIDE | CHECK_FALL | CHECK_FACING | CHECK_CRASH)) {
        return;
    }

    DecelerateX(0x2000);
    switch (RIC.step_s) {
    case 0:
        if (!(g_GameTimer & 3) && RIC.pose < 6 && RIC.pose > 2) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }
        if (RIC.pose == 6 && RIC.poseTimer == 1) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
        if (RIC.poseTimer < 0) {
            BO6_RicSetCrouch(0, RIC.velocityX);
        }
        break;
    }
}

void BO6_RicStepSlideKick(void) {
    if (g_Ric.padPressed & PAD_SQUARE && g_Ric.unk44 & 0x80) {
        RIC.step = PL_S_JUMP;
        BO6_RicSetAnimation(D_us_801820E4);
        BO6_RicSetSpeedX((s32)0xFFFE8000);
        RIC.velocityY = (s32)0xFFFC8000;
        RIC.step_s = 2;
        g_Ric.unk44 = (g_Ric.unk44 | 0xA) & ~4;
        return;
    }
    DecelerateX(0x1000);
    RIC.velocityY += 0x1000;
    if (g_Ric.vram_flag & TOUCHING_GROUND) {
        g_CurrentEntity->velocityX /= 2;
        BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
        RIC.facingLeft++;
        RIC.facingLeft &= 1;
        BO6_RicSetCrouch(3, RIC.velocityX);
        g_api.PlaySfx(SFX_STOMP_SOFT_A);
        return;
    }
    if (RIC.velocityX < 0) {
        if (g_Ric.padPressed & PAD_RIGHT) {
            DecelerateX(0x2000);
        }
        if (RIC.velocityX > (s32)0xFFFD0000 ||
            (g_Ric.vram_flag & TOUCHING_L_WALL)) {
            RIC.facingLeft++;
            RIC.facingLeft &= 1;
            RIC.velocityX /= 2;
            BO6_RicSetAnimation(D_us_80182310);
            g_Ric.unk44 = 0xA;
            RIC.step_s = 2;
            RIC.step = PL_S_JUMP;
        }
    }
    if (RIC.velocityX > 0) {
        if (g_Ric.padPressed & PAD_LEFT) {
            DecelerateX(0x2000);
        }
        if (RIC.velocityX < 0x30000 ||
            (g_Ric.vram_flag & TOUCHING_R_WALL)) {
            RIC.facingLeft++;
            RIC.facingLeft &= 1;
            RIC.velocityX /= 2;
            BO6_RicSetAnimation(D_us_80182310);
            g_Ric.unk44 = 0xA;
            RIC.step_s = 2;
            RIC.step = PL_S_JUMP;
        }
    }
}

void BO6_RicStepBladeDash(void) {
    DecelerateX(0x1C00);

    if (RIC.poseTimer < 0) {
        g_Ric.unk46 = 0;
        BO6_RicSetStand(0);
    } else if (RIC.pose >= 0x12 && !(g_Ric.vram_flag & TOUCHING_GROUND)) {
        g_Ric.unk46 = 0;
        BO6_RicSetFall();
    } else {
        if (!(g_GameTimer & 3) && RIC.pose < 0x12 &&
            g_Ric.vram_flag & TOUCHING_GROUND) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(BP_SLIDE, 2), 0);
        }

        if (RIC.pose == 18 && RIC.poseTimer == 1 &&
            (g_Ric.vram_flag & TOUCHING_GROUND)) {
            BO6_RicCreateEntFactoryFromEntity(
                g_CurrentEntity, BP_SKID_SMOKE, 0);
        }
    }
}

void func_us_801B8E80(s32 arg0) {
    s16 xOff;

    xOff = 3;
    if (RIC.facingLeft) {
        xOff = -3;
    }
    RIC.posY.i.hi -= 0x10;
    RIC.posX.i.hi += xOff;
    BO6_RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
    RIC.posY.i.hi += 0x10;
    RIC.posX.i.hi -= xOff;
    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        RIC.velocityX = 0;
        RIC.velocityY = 0;
    }
}

void BO6_RicStepHighJump(void) {
    bool loadAnim;

    loadAnim = false;
    g_Ric.high_jump_timer++;
    switch (RIC.step_s) {
    case 0:
        if (g_Ric.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (RIC.facingLeft) {
                if (!(g_Ric.padPressed & PAD_LEFT)) {
                    DecelerateX(0x1000);
                }
            } else {
                if (!(g_Ric.padPressed & PAD_RIGHT)) {
                    DecelerateX(0x1000);
                }
            }
        } else {
            DecelerateX(0x1000);
        }

        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            func_us_801B8E80(3);
            g_Ric.high_jump_timer = 0;
            RIC.step_s = 2;
        } else if (g_Ric.high_jump_timer >= 0x1D) {
            RIC.step_s = 1;
            RIC.velocityY = -0x60000;
        }
        break;
    case 1:
        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            RIC.step_s = 2;
            func_us_801B8E80(3);
            g_Ric.high_jump_timer = 0;
        } else {
            RIC.velocityY += 0x6000;
            if (RIC.velocityY > 0x8000) {
                loadAnim = true;
            }
        }
        break;
    case 2:
        if (g_Ric.high_jump_timer >= 5) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        BO6_RicSetAnimation(D_us_801820BC);
        BO6_RicSetStep(PL_S_JUMP);
    }
}
