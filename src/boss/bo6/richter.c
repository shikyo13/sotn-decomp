// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"
#include "sfx.h"

// From ric.h, not included in bo6.h
enum RicInputChecks {
    CHECK_GROUND = 1,
    CHECK_FALL = 4,
    CHECK_FACING = 8,
    CHECK_JUMP = 0x10,
    CHECK_CRASH = 0x40,
    CHECK_80 = 0x80,
    CHECK_GRAVITY_HIT = 0x200,
    CHECK_ATTACK = 0x1000,
    CHECK_CROUCH = 0x2000,
    CHECK_GRAVITY_FALL = 0x8000,
    CHECK_GRAVITY_JUMP = 0x10000,
    CHECK_GROUND_AFTER_HIT = 0x20000,
    CHECK_SLIDE = 0x40000,
};

extern u16 D_us_801D165E;
extern u16 D_us_801D1666;
extern u16 D_us_801D165A;
extern s32 D_us_801D07F8;
extern s32 D_us_801CF3C8;
extern s32 D_us_801CF3CC;

extern AnimationFrame D_us_80181F24[];
extern AnimationFrame D_us_801820B0[];
extern AnimationFrame D_us_801820BC[];

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4BD0);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4EAC);

static void BO6_CheckBladeDashInput(void) {
    if (RIC.step - 1 < 2u || RIC.step == 3 || RIC.step - 4 < 2u) {
        if (D_us_801D165E) {
            return;
        }
        if (g_Ric.padTapped & PAD_SQUARE) {
            func_us_801BA9D0();
        }
    }
}

static void BO6_CheckHighJumpInput(void) {
    if (RIC.step == PL_S_CROUCH || RIC.step == PL_S_STAND ||
        (RIC.step == PL_S_JUMP && RIC.velocityY > FIX(1)) ||
        RIC.step == PL_S_FALL) {
        if (D_us_801D165E) {
            return;
        }
        if (g_Ric.padTapped & PAD_UP) {
            func_us_801BA050();
        }
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicMain);

void func_us_801B5A14(s32 arg0) {
    D_us_801CF3C8 = arg0;
    D_us_801CF3CC = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", RichterThinking);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B6998);

#ifndef NON_MATCHING
INCLUDE_ASM("boss/bo6/nonmatchings/richter", EntityRichter);
#else
extern EInit D_us_80180400;
extern s32 D_us_801CF3E0;
extern s32 D_us_801CF3E4;
extern u16 D_us_801D1686;
void EntityRichter(Entity* self) {
    s32 i;
    Entity* entity;
    u16 hp;

    g_Ric.unk6A = RIC.hitPoints;
    if (self->step == 0) {
        InitializeEntity((u16*)&D_us_80180400);
        func_us_801B4BD0();
        i = 0x44;
        entity = &g_Entities[0x44];
        do {
            DestroyEntity(entity);
            i++;
            entity++;
        } while (i < 0x90);
        hp = RIC.hitPoints;
        D_us_801D1686 = hp;
        D_us_801CF3E0 = 0;
        g_Ric.unk6C = hp;
        g_Ric.unk6A = hp;
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
#endif

extern AnimationFrame D_us_80181F1C[];
extern AnimationFrame D_us_80182130[];
extern AnimationFrame D_us_801822B8[];
void BO6_RicStepStand(void) {
    s32 facing;

    if (!BO6_RicCheckInput(
            CHECK_FALL | CHECK_FACING | CHECK_JUMP | CHECK_CRASH |
            CHECK_ATTACK | CHECK_CROUCH | CHECK_SLIDE)) {
        DecelerateX(FIX(0.125));
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
        case 64:
            BO6_DisableAfterImage(1, 1);
            if (RIC.pose < 3) {
                facing = BO6_RicCheckFacing();
                if (g_Ric.padPressed & PAD_DOWN) {
                    RIC.step = PL_S_CROUCH;
                    RIC.anim = D_us_80182130;
                    break;
                }
            }
            if (RIC.poseTimer < 0) {
                if (g_Ric.padPressed & PAD_SQUARE) {
                    D_us_801D165E = 2;
                    RIC.step_s++;
                    BO6_RicSetAnimation(D_us_801822B8);
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                    break;
                }
                D_us_801D165E = 0;
                BO6_RicSetStand(0);
            }
            break;
        case 65:
            BO6_DisableAfterImage(1, 1);
            if (g_Ric.padPressed & PAD_SQUARE) {
                break;
            }
            D_us_801D165E = 0;
            BO6_RicSetStand(0);
            break;
        case 66:
            BO6_DisableAfterImage(1, 1);
            if (RIC.pose < 3) {
                BO6_RicCheckFacing();
            }
            if (RIC.poseTimer < 0) {
                D_us_801D165E = 0;
                BO6_RicSetStand(0);
            }
            break;
        }
    }
}

void BO6_RicStepWalk(void) {
    if (!BO6_RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP |
                           CHECK_CRASH | CHECK_ATTACK | CHECK_CROUCH)) {
        DecelerateX(FIX(0.125));
        if (BO6_RicCheckFacing() == 0) {
            BO6_RicSetStand(0);
            return;
        }
        if (RIC.step_s != 0) {
            if (RIC.step_s) {
            }
        } else {
            BO6_RicSetSpeedX(FIX(1.25));
        }
    }
}

void BO6_RicStepRun(void) {
    g_Ric.timers[PL_T_8] = 8;
    g_Ric.timers[PL_T_CURSE] = 8;
    if (!BO6_RicCheckInput(CHECK_FALL | CHECK_FACING | CHECK_JUMP |
                           CHECK_CRASH | CHECK_ATTACK | CHECK_CROUCH)) {
        DecelerateX(FIX(0.125));
        if (BO6_RicCheckFacing() == 0) {
            BO6_RicSetStand(0);
            if (g_Ric.timers[PL_T_RUN] == 0) {
                if (!(g_Ric.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL))) {
                    BO6_RicSetAnimation(D_us_80181F24);
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
            } else {
                RIC.velocityX = 0;
            }
            return;
        }
        if (RIC.step_s != 0) {
            if (RIC.step_s) {
            }
        } else {
            BO6_RicSetSpeedX(FIX(2.25));
        }
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepJump);

void BO6_RicStepFall(void) {
    if (BO6_RicCheckInput(
            CHECK_GROUND | CHECK_FACING | CHECK_ATTACK | CHECK_GRAVITY_FALL)) {
        return;
    }
    DecelerateX(FIX(1. / 16));
    switch (RIC.step_s) {
    case 0:
        if (g_Ric.timers[PL_T_5] && g_Ric.padTapped & PAD_CROSS) {
            func_us_801B9E70();
        } else if (BO6_RicCheckFacing()) {
            BO6_RicSetSpeedX(FIX(0.75));
        }
        break;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepCrouch);
#else
extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182068[];
extern AnimationFrame D_us_80182110[];
extern AnimationFrame D_us_801822C0[];
void BO6_RicStepCrouch(void) {
    s32 facing;

    if (!BO6_RicCheckInput(
            CHECK_FALL | CHECK_FACING | CHECK_ATTACK | CHECK_SLIDE)) {
        DecelerateX(FIX(0.125));
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
                facing = BO6_RicCheckFacing();
                if (!(g_Ric.padPressed & PAD_DOWN)) {
                    RIC.step = PL_S_STAND;
                    RIC.anim = D_us_80182110;
                    return;
                }
            }
            if (RIC.poseTimer < 0) {
                if (g_Ric.padPressed & PAD_SQUARE) {
                    D_us_801D165E = 2;
                    RIC.step_s++;
                    BO6_RicSetAnimation(D_us_801822C0);
                    BO6_RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_ARM_BRANDISH_WHIP, 0);
                    return;
                }
                D_us_801D165E = 0;
                RIC.step_s = 0;
                BO6_RicSetAnimation(D_us_80182048);
            }
            break;
        case 0x41:
            BO6_DisableAfterImage(1, 1);
            if (!(g_Ric.padPressed & PAD_SQUARE)) {
                D_us_801D165E = 0;
                RIC.step_s = 0;
                BO6_RicSetAnimation(D_us_80182048);
            }
            break;
        }
    }
}
#endif

void BO6_RicResetPose(void) {
    RIC.pose = RIC.poseTimer = 0;
    g_Ric.unk44 = 0;
    D_us_801D165E = 0;
    RIC.drawFlags &= ~ENTITY_ROTATE;
}

void func_us_801B77D8(void) {
    s32 diff;

    diff = RIC.posX.i.hi - PLAYER.posX.i.hi;
    if (diff <= 0) {
        RIC.entityRoomIndex = 0;
    } else {
        RIC.entityRoomIndex = 1;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHit);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepDead);

void BO6_RicStepStandInAir(void) {
    if (RIC.step_s == 0) {
        RIC.velocityY += 0x3800;
        if (RIC.velocityY > 0) {
            RIC.velocityY = 0;
            RIC.step_s = 1;
        }
    } else if (D_us_801D1666) {
        D_us_801D165E = 0;
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
        D_us_801D165E = 0;
        BO6_RicCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_RIC_BLINK, 0x45), 0);
        g_Ric.timers[PL_T_POISON] = 0x800;
    }
}

void BO6_RicStepHydrostorm(void) {
    if (RIC.poseTimer < 0) {
        BO6_RicSetStand(0);
        D_us_801D165E = 0;
    }
}

void BO6_RicStepGenericSubwpnCrash(void) {
    if (D_us_801D1666) {
        BO6_RicSetStand(0);
        D_us_801D165E = 0;
    }
}

void BO6_RicStepThrowDaggers(void) {
    if (RIC.step_s == 0) {
        D_us_801D07F8 = 0x200;
        RIC.step_s++;
    } else {
        BO6_RicCheckFacing();
        if (!--D_us_801D07F8) {
            D_us_801D165E = 0;
            BO6_RicSetStand(0);
            D_us_801D1666 = 1;
        }
    }
    if (g_Ric.padTapped & PAD_CROSS) {
        func_us_801B9E70();
        D_us_801D165E = 0;
        D_us_801D1666 = 1;
        D_us_801D07F8 = 0;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlideKick);

void BO6_RicStepBladeDash(void) {
    DecelerateX(0x1C00);

    if (RIC.poseTimer < 0) {
        D_us_801D165E = 0;
        BO6_RicSetStand(0);
    } else if (RIC.pose >= 0x12 && !(g_Ric.vram_flag & TOUCHING_GROUND)) {
        D_us_801D165E = 0;
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

void func_us_801B8E80(u16 arg0) {
    s16 xMod = 3;
    if (RIC.facingLeft) {
        xMod = -xMod;
    }

    RIC.posY.i.hi -= 16;
    RIC.posX.i.hi += xMod;
    BO6_RicCreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(BP_EMBERS, 1), 0);
    RIC.posY.i.hi += 16;
    RIC.posX.i.hi -= xMod;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
    }
    if (arg0 & 2) {
        RIC.velocityX = 0;
        RIC.velocityY = 0;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHighJump);
#else
void BO6_RicStepHighJump(void) {
    s32 setFall;

    D_us_801D165A++;
    setFall = 0;
    switch (RIC.step_s) {
    case 0:
        if ((g_Ric.padPressed & (PAD_LEFT | PAD_DOWN)) &&
            (RIC.facingLeft ? (g_Ric.padPressed & PAD_LEFT)
                            : (g_Ric.padPressed & PAD_DOWN))) {
        } else {
            DecelerateX(FIX(0.25));
        }
        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            func_us_801B8E80(3);
            D_us_801D165A = 0;
            RIC.step_s = 2;
        } else if (D_us_801D165A >= 0x1D) {
            RIC.step_s = 1;
            RIC.velocityY = FIX(-6);
        }
        break;
    case 1:
        if (g_Ric.vram_flag & TOUCHING_CEILING) {
            RIC.step_s = 2;
            func_us_801B8E80(3);
            D_us_801D165A = 0;
        } else {
            RIC.velocityY += FIX(1.5);
            if (FIX(2) < RIC.velocityY) {
                setFall = 1;
            }
        }
        break;
    case 2:
        if (D_us_801D165A >= 5) {
            setFall = 1;
        }
        break;
    }
    if (setFall) {
        BO6_RicSetAnimation(D_us_801820BC);
        BO6_RicSetStep(PL_S_JUMP);
    }
}
#endif
