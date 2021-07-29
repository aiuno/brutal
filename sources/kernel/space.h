#pragma once

#include "kernel/memory.h"
#include "kernel/vmm.h"

typedef struct
{
    VmmRange range;
    MemObj *object;
    size_t offset;
} MemoryMapping;

typedef struct
{
    OBJECT_HEADER;

    BrSpaceFlags flags;
    Lock lock;
    VmmSpace vmm;
    Vec(MemoryMapping *) mappings;
    RangeAlloc alloc;
} Space;

Space *space_create(BrSpaceFlags flags);

void space_ref(Space *self);

void space_deref(Space *self);

void space_switch(Space *self);

typedef Result(BrResult, VmmRange) SpaceResult;

SpaceResult space_map(Space *self, MemObj *mem_obj, size_t offset, size_t size, uintptr_t vaddr);

void space_unmap(Space *self, VmmRange range);

void space_dump(Space *self);
