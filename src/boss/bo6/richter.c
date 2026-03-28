// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern s32 D_us_801CF3C8;
extern s32 D_us_801CF3CC;
extern AnimationFrame D_us_801820B0[];

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4BD0);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B4EAC);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckBladeDashInput);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_CheckHighJumpInput);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicMain);

void func_us_801B5A14(s32 arg0) {
    D_us_801CF3C8 = arg0;
    D_us_801CF3CC = 0;
}

INCLUDE_ASM("boss/bo6/nonmatchings/richter", RichterThinking);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B6998);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", EntityRichter);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepStand);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepRun);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepEnableFlameWhip);

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

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepThrowDaggers);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlide);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepSlideKick);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepBladeDash);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", func_us_801B8E80);

INCLUDE_ASM("boss/bo6/nonmatchings/richter", BO6_RicStepHighJump);
