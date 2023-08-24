#pragma once

#if _WIN64
#define PIKAFISH_API __declspec(dllexport)
#elif defined(NN_NINTENDO_SDK)
#define PIKAFISH_API
#endif // 0



extern "C" {
	PIKAFISH_API void PAIP_init();
	PIKAFISH_API void PAIP_run(const char* command);
	PIKAFISH_API void PAIP_shutdown();
	PIKAFISH_API void PAIP_set_output_callback(void (*on_output_callback)(const char*));
}
