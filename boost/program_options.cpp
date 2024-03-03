#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>

int main(int argc, char *argv[])
{
    try
    {
        boost::program_options::options_description desc("print person info");
        desc.add_options()("help", "produce help message")(
            "name", boost::program_options::value<std::string>(), "set name")(
            "age", boost::program_options::value<std::uint16_t>(), "set age");

        boost::program_options::variables_map vm;
        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        for (auto &op : vm)
        {
            std::cout << op.first << ": " << op.second.as<std::string>()
                      << std::endl;
        }
        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return 0;
        }

        else if (vm.contains("name"))
        {
            std::cout << "The person name is " << vm["name"].as<std::string>()
                      << std::endl;
        }

        else if (vm.count("age"))
        {
            std::cout << "The person age is " << vm["age"].as<std::uint16_t>()
                      << std::endl;
        }

        else
        {
            std::cout << "Nothing" << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}