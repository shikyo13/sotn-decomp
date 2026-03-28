// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

extern AnimationFrame ric_anim_stand[];
extern AnimationFrame D_us_80182038[];
extern AnimationFrame D_us_80182048[];
extern AnimationFrame D_us_80182050[];
extern AnimationFrame D_us_80182058[];
extern AnimationFrame D_us_801822D8[];
extern AnimationFrame D_us_801821F8[];
extern AnimationFrame D_us_80182304[];
extern AnimationFrame D_us_80182310[];
extern AnimationFrame D_us_80182010[];
extern AnimationFrame D_us_801820BC[];
extern AnimationFrame D_us_80182078[];
extern AnimationFrame D_us_80182094[];
extern AnimationFrame D_us_80182324[];
extern AnimationFrame D_us_80182360[];
extern EInit D_us_8018043C;
extern EInit D_us_80180448;
extern AnimationFrame D_us_80181554[];
extern AnimationFrame D_us_80181A40[];
extern s32 D_us_801D084C;
extern EInit D_us_80180424;
extern EInit D_us_80180430;

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

void BO6_DisableAfterImage(s32 resetAnims, s32 arg1) {
    Primitive* prim;

    if (resetAnims) {
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
            .ext.disableAfterImage.resetFlag = 1;
        g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].animCurFrame =
            g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_2].animCurFrame =
                g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_3].animCurFrame =
                    0;
        prim = &g_PrimBuf
            [g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1].primIndex];
        while (prim) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
        .ext.disableAfterImage.disableFlag = 1;
    g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
        .ext.disableAfterImage.index = MaxAfterImageIndex;
    if (arg1) {
        g_Ric.timers[PL_T_AFTERIMAGE_DISABLE] = 4;
    }
}

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

void func_us_801B9D74(void) {
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_RUN);
    BO6_RicSetAnimation(D_us_801821F8);
    BO6_RicSetSpeedX(0x24000);
    g_Ric.timers[PL_T_RUN] = 40;
    RIC.velocityY = 0;
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_SMOKE_PUFF, 5), 0);
}

void func_us_801B9DE4(void) {
    if (g_Ric.timers[PL_T_8]) {
        func_us_801B9D74();
        return;
    }
    g_Ric.timers[PL_T_CURSE] = 8;
    g_Ric.timers[PL_T_8] = 12;
    g_Ric.timers[PL_T_CURSE] = 12;
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_WALK);
    BO6_RicSetAnimation(D_us_80182010);
    BO6_RicSetSpeedX(0x14000);
    RIC.velocityY = 0;
}

void func_us_801B9E70(void) {
    if (BO6_RicCheckFacing() || RIC.step == PL_S_SLIDE) {
        BO6_RicSetAnimation(D_us_80182094);
        if (RIC.step == PL_S_RUN) {
            BO6_RicSetSpeedX(0x24000);
            g_Ric.unk44 = 0x10;
        } else {
            BO6_RicSetSpeedX(0x14000);
            g_Ric.unk44 = 0;
        }
    } else {
        BO6_RicSetAnimation(D_us_80182078);
        RIC.velocityX = 0;
        g_Ric.unk44 = 4;
    }
    BO6_RicSetStep(PL_S_JUMP);
    RIC.velocityY = -0x4B000;
}

void BO6_RicSetFall(void) {
    if (g_Ric.prev_step != PL_S_RUN && g_Ric.prev_step != PL_S_SLIDE) {
        RIC.velocityX = 0;
    }
    if (g_Ric.prev_step != PL_S_WALK && g_Ric.prev_step != PL_S_RUN) {
        BO6_RicSetAnimation(D_us_801820BC);
    }
    if (g_Ric.prev_step == PL_S_RUN) {
        g_Ric.unk44 = 0x10;
    }
    BO6_RicSetStep(PL_S_FALL);
    RIC.velocityY = 0x20000;
    g_Ric.timers[PL_T_5] = 8;
    g_Ric.timers[PL_T_6] = 8;
    g_Ric.timers[PL_T_CURSE] = 0;
    g_Ric.timers[PL_T_8] = 0;
    if (g_Ric.prev_step == PL_S_SLIDE) {
        g_Ric.timers[PL_T_5] = g_Ric.timers[PL_T_6] = 0;
        RIC.pose = 2;
        RIC.poseTimer = 0x10;
        RIC.velocityX /= 2;
    }
}

void func_us_801BA050(void) {
    BO6_RicSetStep(PL_S_HIGHJUMP);
    RIC.velocityX = 0;
    BO6_RicSetSpeedX(0x14000);
    RIC.velocityY = -0x78000;
    g_Ric.high_jump_timer = 0;
    BO6_RicSetAnimation(D_us_80182324);
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_HIGH_JUMP, 0);
    g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_B);
    g_Ric.timers[PL_T_12] = 4;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicCheckSubwpnChainLimit);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoSubweapon);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoAttack);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicDoCrash);

void BO6_RicSetDeadPrologue(void) { BO6_RicSetStep(PL_S_DEAD_PROLOGUE); }

void BO6_RicSetSlide(void) {
    BO6_RicCheckFacing();
    BO6_RicSetStep(PL_S_SLIDE);
    BO6_RicSetAnimation(D_us_801822D8);
    g_CurrentEntity->velocityY = 0;
    BO6_RicSetSpeedX(0x58000);
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_BOSS_RIC_SLIDE_SKID);
    g_Ric.timers[PL_T_12] = 4;
}

void BO6_RicSetSlideKick(void) {
    g_Ric.unk44 = 0;
    BO6_RicSetStep(PL_S_SLIDE_KICK);
    BO6_RicSetAnimation(D_us_80182304);
    g_CurrentEntity->velocityY = -0x20000;
    BO6_RicSetSpeedX(0x58000);
    func_us_801B9C14();
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_25, 0);
    g_api.PlaySfx(SFX_BOSS_RIC_ATTACK_A);
    g_Ric.timers[PL_T_12] = 4;
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_31, 0);
}

void func_us_801BA9D0(void) {
    BO6_RicSetStep(PL_S_BLADEDASH);
    BO6_RicSetAnimation(D_us_80182360);
    g_CurrentEntity->velocityY = 0;
    BO6_RicSetSpeedX(0x58000);
    g_Ric.unk46 = 5;
    g_Ric.timers[PL_T_12] = 4;
    BO6_RicCreateEntFactoryFromEntity(g_CurrentEntity, BP_BLADE_DASH, 0);
    func_us_801B9C14();
    g_api.PlaySfx(SFX_BOSS_RIC_DASH_ATTACK);
    g_api.PlaySfx(SFX_RIC_SLIDE_SKID);
}

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

void BO6_RicEntityHitByDark(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = RIC.zPriority + 2;
        entity->palette = 0x819F;
        if (D_us_801D084C & 1) {
            entity->blendMode = BLEND_TRANSP | BLEND_QUARTER;
        } else {
            entity->blendMode = BLEND_TRANSP;
        }
        D_us_801D084C++;
        entity->opacity = 0xFF;
        entity->drawFlags =
            ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_MASK_R | ENTITY_MASK_G;
        entity->scaleX = entity->scaleY = 0x40;
        entity->anim = D_us_80181554;
        entity->posY.i.hi += (rand() % 35) - 15;
        entity->posX.i.hi += (rand() % 20) - 10;
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;
    case 1:
        if (entity->opacity > 16) {
            entity->opacity -= 8;
        }
        entity->posY.val += entity->velocityY;
        entity->scaleX += 8;
        entity->scaleY += 8;
        if (entity->poseTimer < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_us_801BBBC0(void) {}

void func_us_801BBBC8(void) {}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BBBD0);

Entity* BO6_RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity = BO6_RicGetFreeEntity(
        STAGE_ENTITY_START + 4, STAGE_ENTITY_START + 16);
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = E_FACTORY;
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    entity->zPriority = source->zPriority;
    return entity;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityFactory);

void func_us_801BC2F0(Entity* self) {
    if (RIC.step != PL_S_SLIDE) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(&D_us_8018043C);
        self->ext.ILLEGAL.u16[0] = self->hitboxState;
        self->flags = 0x18000000;
        self->hitboxOffX = 0x14;
        self->hitboxOffY = 0xC;
        self->hitboxWidth = 9;
        self->hitboxHeight = 9;
        self->step = 1;
    }
    self->hitboxState = self->ext.ILLEGAL.u16[0];
    if (RIC.pose < 2) {
        self->hitboxState = 0;
    }
    if (RIC.pose >= 8) {
        DestroyEntity(self);
    }
}

void func_us_801BC3E0(Entity* self) {
    if (RIC.step != PL_S_SLIDE_KICK) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(&D_us_80180448);
        self->flags = 0x18000000;
        self->hitboxOffX = 0x14;
        self->hitboxWidth = 9;
        self->hitboxHeight = 9;
        self->step = 1;
    }
    if (RIC.animCurFrame == 0x8C) {
        self->hitboxOffY = 0;
    }
    if (RIC.animCurFrame == 0x8D) {
        self->hitboxOffY = 0xC;
    }
    if (self->hitFlags) {
        g_Ric.unk44 |= 0x80;
    } else {
        g_Ric.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

void func_us_801BC4F8(Entity* self) {
    if (RIC.step != PL_S_BLADEDASH) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(&D_us_80180424);
        self->flags = 0x18000000;
        self->hitboxHeight = 0x14;
        self->hitboxWidth = 0x14;
        self->hitboxHeight = 0xC;
        self->hitboxWidth = 0xC;
        self->hitboxOffY = 0;
        self->hitboxOffX = 0;
        self->ext.ILLEGAL.u16[0x1A] = 0x11;
        self->step++;
    }
    if (RIC.pose >= 0x13) {
        DestroyEntity(self);
    }
}

void func_us_801BC5C8(Entity* self) {
    if (RIC.step != PL_S_HIGHJUMP) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = RIC.posX.i.hi;
    self->posY.i.hi = RIC.posY.i.hi;
    self->facingLeft = RIC.facingLeft;
    if (!self->step) {
        InitializeEntity(&D_us_80180430);
        self->flags = 0x18000000;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0xC;
        self->step = 1;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BC678);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityHitByCutBlood);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD0B8);

void func_us_801BD384(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = 2;
        self->anim = D_us_80181A40;
        self->flags = 0x28000000;
        self->zPriority = RIC.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) + 0xFFFF0000;
        self->step++;
        break;
    case 1:
        if (self->pose == 6 && self->poseTimer == 1 && (rand() & 1)) {
            BO6_RicCreateEntFactoryFromEntity(self, BP_EMBERS, 0);
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", func_us_801BD47C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_39144", BO6_RicEntityPlayerBlinkWhite);
