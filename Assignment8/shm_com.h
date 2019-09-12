#define TEXT_LIMIT 2048

struct shared_use_st{
	int written_by;
	char text_space[TEXT_LIMIT];
};