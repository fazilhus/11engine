baseName = path.getbasename(os.getcwd());

project (baseName)
    kind "ConsoleApp"
    location "./"

    files {"**.hpp", "**.h", "**.cpp","**.c"}

    includedirs {
        "./",
        "include",
        "src"
    }

    vpaths {
        ["Header Files/*"] = { "**.h" },
        ["Source Files/*"] = { "**.cpp" },
    }

    link_to "core"
    link_to "doctest"