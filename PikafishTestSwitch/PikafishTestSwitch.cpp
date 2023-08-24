// PikafishTestSwitch.cpp : Defines the entry point to the NintendoSDK application.
//
#include <cstdlib>
#include <cstring>
#include <new>
#include <thread>
#include <nn/fs.h>
#include <nn/nn_Assert.h>
#include <nn/nn_Log.h>
#include <nn/nn_Abort.h>

#include "papi/papi.h"
#include "nn/nn_Log.h"




extern "C" void nnMain()
{
    nn::Result result;

    size_t cacheSize = 0;

    char* cacheBuffer = nullptr;

    // Mounts the file system.
    // Mounting requires a cache buffer.
    {
        NN_LOG("Mount Rom\n");

        // Gets the buffer size needed for the file system metadata cache.
        // No error handling is required because the library cancels the operation if it fails to get any data.
        (void)nn::fs::QueryMountRomCacheSize(&cacheSize);

        // Allocates the cache buffer.
        cacheBuffer = new(std::nothrow) char[cacheSize];
        if (cacheBuffer == nullptr)
        {
            NN_ASSERT(false, "Cache buffer is null.\n");
            return;
        }

        // Mounts the file system.
        // Do not release the cache buffer until you unmount.
        result = nn::fs::MountRom("rom", cacheBuffer, cacheSize);
        // Always abort when a failure occurs.
        NN_ABORT_UNLESS_RESULT_SUCCESS(result);
    }

	PAIP_init();
    // PAIP_run("setoption name Threads value 2");
    PAIP_run("setoption name EvalFile value rom:/test/pikafish.nnue");
	PAIP_run("go depth 1");
    //std::this_thread::sleep_for(std::chrono::microseconds(10000));
	PAIP_shutdown();

    {
        NN_LOG("Unmount Rom\n");

        nn::fs::Unmount("rom");

        // Releases the cache buffer.
        delete[] cacheBuffer;
        cacheBuffer = nullptr;
    }
    return;
}
