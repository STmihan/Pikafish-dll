using System.Runtime.InteropServices;

namespace PikafishCsCli
{
    public static class PApi
    {
        [DllImport("Pikafish.dll", EntryPoint = "PAIP_init", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PApiInit();

        [DllImport("Pikafish.dll", EntryPoint = "PAIP_run", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PApiRun(string command);

        [DllImport("Pikafish.dll", EntryPoint = "PAIP_shutdown", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PApiShutdown();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void OutputCallback(string output);

        [DllImport("Pikafish.dll", EntryPoint = "PAIP_set_output_callback",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void PApiSetOutputCallback(OutputCallback callback);
    }
}