#include "cxxopts.hh"
#include <yaml-cpp/yaml.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <sstream>
#include <fstream>

std::string configPath;
std::string execPath;

struct Action {
   std::string flag;
   std::string description;
   std::string exec;
};

void operator >> (const YAML::Node& node, Action& action) {
   action.flag = node["flag"].as<std::string>();
   action.description = node["description"].as<std::string>();
   action.exec = node["exec"].as<std::string>();
}

Action getAction(std::string flag) {
    YAML::Node config = YAML::LoadFile(configPath);

    Action result;
    const unsigned int numActions = config.size();
    for(unsigned index = 0; index < numActions; index++) {
        Action action;
        config[index] >> action;
        if (flag == action.flag) {
            result = action;
            break;
        }
    }

    std::ofstream fout(configPath);
    fout << config;

    return result;
}

void parse(int argc, const char* argv[]) {
    try {
        cxxopts::Options options(argv[0], "Starter command line executer\n");
        options.positional_help("[optional args]")
            .show_positional_help();

        options.set_width(70)
            .set_tab_expansion()
            .allow_unrecognised_options()
            .add_options()
            ("e,executable", "Executable to run", cxxopts::value<std::string>())
            ("s,show", "Show config options")
            ("h,help", "Print help")
        #ifdef CXXOPTS_USE_UNICODE
        ("unicode", u8"A help option with non-ascii: à. Here the size of the"
            " string should be correct")
        #endif
        ;

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help({"", "Group"}) << std::endl;
            exit(0);
        }

        if (result.count("show")) {
            std::string cmd = "cat " + configPath;
            system(cmd.c_str());
            exit(0);
        }

        if (result.count("executable")) {
            std::string flag = result["executable"].as<std::string>();
            Action action = getAction(flag);
            if (action.flag.empty()) {
                std::cout << "No executable found for flag: " << flag << std::endl;
            } else {
                std::cout << "Description: " << action.description << std::endl;
                std::string cmd = execPath + action.exec;
                system(cmd.c_str());
            }
        }

        if (0 == result.arguments().size() || result.unmatched().size() > 0) {
            std::cout << "Use help flag!" << std::endl;
        }

    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

void setPaths() {
    const char *homePath;
    if ((homePath = getenv("HOME")) == NULL) {
        homePath = getpwuid(getuid())->pw_dir;
    }
    configPath = std::string(homePath) + std::string("/.starter/config.yaml");
    execPath = std::string(homePath) + std::string("/.starter/executables/");
}

int main(int argc, const char* argv[]) {
    setPaths();
    parse(argc, argv);

    return 0;
}