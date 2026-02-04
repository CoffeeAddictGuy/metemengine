#pragma once

typedef void (*OnInitFn)(void *self);
typedef void (*OnUpdateFn)(void *self, float dt);
typedef void (*OnDestroyFn)(void *self);
