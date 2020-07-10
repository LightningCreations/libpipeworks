typedef struct pw_sprite pw_sprite;

pw_sprite* pw_init_sprite(float x, float y, float width, float height, float depth, uint32_t numFrames, const char *const *const frames); // All the consts

void pw_sprite_add_update_handler(void(*handler)(pw_sprite *sprite));

void pw_sprite_set_x(float x);
void pw_sprite_set_y(float y);
float pw_sprite_get_x();
float pw_sprite_get_y();
void pw_sprite_set_pos(float x, float y);

void pw_sprite_set_width(float width);
void pw_sprite_set_height(float height);
float pw_sprite_get_width();
float pw_sprite_get_height();
void pw_sprite_set_size(float width, float height);

void pw_sprite_set_pos_and_size(float x, float y, float width, float height);

void pw_sprite_set_frame(uint32_t id);
