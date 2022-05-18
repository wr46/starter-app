#include <iostream>

#include "cxxopts.hh"

void
parse(int argc, const char* argv[])
{
  try
  {
    cxxopts::Options options(argv[0], "[ Starter command line options ]\n");
    options
      .positional_help("[optional args]")
      .show_positional_help();

    options
      .set_width(70)
      .set_tab_expansion()
      .allow_unrecognised_options()
      .add_options()
      ("e,executable", "Executable to run", cxxopts::value<std::string>())
      ("help", "Print help")
    #ifdef CXXOPTS_USE_UNICODE
      ("unicode", u8"A help option with non-ascii: à. Here the size of the"
        " string should be correct")
    #endif
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }

    if (result.count("executable"))
    {
      std::cout << "Executable = " << result["executable"].as<std::string>()
        << std::endl;
    }

    std::cout << "Arguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

    std::cout << "Unmatched options: ";
    for (const auto& option: result.unmatched())
    {
      std::cout << "'" << option << "' ";
    }
    std::cout << std::endl;
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

int main(int argc, const char* argv[])
{
  parse(argc, argv);

  return 0;
}