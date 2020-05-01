#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "dependencies/argh/argh.h"
#include "dependencies/curlpp/include/curlpp/cURLpp.hpp"
#include "dependencies/curlpp/include/curlpp/Easy.hpp"
#include "dependencies/curlpp/include/curlpp/Options.hpp"

using namespace argh;
using namespace curlpp;
using namespace curlpp::options;
using namespace std;

/// Callback must be declared static, otherwise it won't link...
size_t WriteCallback(char *ptr, size_t size, size_t nmemb, void *f) {
    FILE *file = (FILE *) f;
    return fwrite(ptr, size, nmemb, file);
};

int main(int, char *argv[]) {
    parser cmdl(argv);
    system("clear");
    cout << "\n----------------- \n\nWelcome To CLI Downloader\n--------------------\n" << endl;
    if (cmdl[{"-h", "--help"}]) {
        cout << "CLI [OPTIONS] [URL]" << endl;
        cout << "Options - \n-h, --help \t\t Show this help\n-d [URL] \t\t downloads "
                "the speciefied and saves it into a file" << endl;
    }
    if (cmdl[{"-d", "--download"}]) {
        cout << "Downloading from the link: " << cmdl[1] << endl;
        auto url = cmdl[1];
        const char *filename = (const char *) cmdl[2];
        cout << "Saving To File: " << filename << endl;
        try {
            Cleanup downloadCleanup;
            Easy req;
            WriteFunctionCurlFunction
                    myFunction(WriteCallback);
            FILE *file = stdout;
            file = fopen(filename, "wb");
            if (file == NULL) {
                fprintf(stderr, "%s/n", strerror(errno));
                return EXIT_FAILURE;
            }
            curlpp::OptionTrait<void *, CURLOPT_WRITEDATA>
                    myData(file);
            req.setOpt<Url>(url);
            req.setOpt(myFunction);
            req.perform();
        } catch (RuntimeError &e) {
            cout << "RuntimeError: " << e.what() << endl;
        }
        catch (LogicError &e) {
            cout << "LogicError: " << e.what() << endl;
        }
    }
    return EXIT_SUCCESS;
}
