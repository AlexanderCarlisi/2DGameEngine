// Stub file to use as a referense for how the Engine should be layed out, and utilized.
//


//
// # includes for WorldHandler
//
//
//

// really this could be done is other files, but this is an example. leave me alone.
//


// overworld0.c or something

// overworld0.c gameobjects

static const size_t BUFFER_SIZE_OVERWORLD0 = 30;
#define BUFFER_I_PLAYER 0
static const size_t BUFFER_I_PLAYER2 = 1;
#define BUFFER_INTERVAL_WALLS (Interval) {2, 19}
static const Interval BUFFER_INTERVAL_FLOORS (Interval) {20, 29}


static const GameObjectConfig OBJ_CONF_PLAYER = {
	.collider_vector = create_empty_collision_box_vector(0),
	.starting_pose = (Pose) {0, 0, 0, 0},
	.staring_rotation = 0.0f,
	.object_type = ObjectType.DYNAMIC
};

static const WorldConfig WRL_CONF_OVERWORLD0 = {
	.buffer_interval = (Interval) {0, BUFFER_SIZE_OVERWORLD0 - 1},
	.pool_interval = NULL,	// Intervals are inclusive, to not delegate any space, set to NULL.
	.pool_size = 20,
	.pixels_per_meter = 10.0f,
	.gravity_field = 9.8f,
	.reallocation_ratio = 1.5f
};


void overworld0_init() {
	printf("init");
	// Buffer and Pool as been allocated once this is called.
	// The Buffer and Pool are allocated with Empty GameObjects, so no need to init anything there
	// We just need to set GameObject values, and 'reserve' them for parts of the game.
	worldhandler_buffer_init_object(BUFFER_I_PLAYER, &OBJ_CONF_PLAYER);
	worldhandler_buffer_init_objects(&BUFFER_INTERVAL_WALLS, (GameObjectConfig) { });

	GameObject* playerPtr = worldhandler_buffer_get_object(BUFFER_I_PLAYER);
	
}

void overworld0_start() {
	printf("start");
}

void overworld0_loop() {
	printf("loop");
}

void overworld0_close() {
	printf("close");
}


// overworld1.c or something
WorldConfig overworld1_world_config = {
	.buffer_interval = (Interval) {30, 99},
	.pool_interval = (Interval) {0, 19},
	.pool_size = 20,
	.pixels_per_meter = 10.0f,
	.gravity_field = 9.8f,
	.reallocation_ratio = 1.25f
};

void overworld1_init() {
	printf("init");
}

void overworld1_start() {
	printf("start");
}

void overworld1_loop() {
	printf("loop");
}

void overworld1_close() {
	printf("close");
}


// back to instance.c
void worlds_free() { }

World overworld0 = {
	.world_config = overworld0_world_config,
	.init = &overworld0_init,
	.start = &overworld0_start,
	.loop = &overworld0_loop,
	.close = &overworld0_close,
	.free = &worlds_free
};

World overworld1 = {
	.world_config = overworld1_world_config,
	.init = &overworld1_init,
	.start = &overworld1_start,
	.loop = &overworld1_loop,
	.close = &overworld1_close,
	.free = &worlds_free
	
};





// TODO: find a way to run this stuff in Engine, prolly just gonna be a header
void initialize() {
	worldhandler_load(&overworld0); // starting world in the game
	worldhandler_load(&overworld1); // load the most likely next world in the game
	worldhandler_set_active(&overworld0); // set starting world as active
}
