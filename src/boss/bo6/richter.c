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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B6998);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepJump);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepCrouch);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHit);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlideKick);

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
