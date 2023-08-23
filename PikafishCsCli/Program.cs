// See https://aka.ms/new-console-template for more information

using PikafishCsCli;

Console.WriteLine("Hello, World!");
PApi.PApiInit();
PApi.PApiSetOutputCallback((output) => Console.WriteLine($"[from callback] {output}"));
PApi.PApiRun("go depth 5");
PApi.PApiShutdown();
