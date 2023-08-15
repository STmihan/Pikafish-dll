// See https://aka.ms/new-console-template for more information

using PikafishCsCli;

Console.WriteLine("Hello, World!");
PApi.PApiInit();
PApi.PApiRun("go depth 5");
PApi.PApiShutdown();
