project "doctest"
    kind "StaticLib"
    language "c++"
    cppdialect "C++23"
    location "./"

    files {
        "doctest/**.h",
        "doctest/**.cpp",
    }

    includedirs {
        "doctest",
        "doctest/extensions",
        "doctest/parts"
    }

    vpaths {
        ["Header Files/*"] = { "doctest/**.h" },
        ["Source Files/*"] = { "doctest/**.cpp" },
    }

    filter("configurations:Debug")
		symbols("On")

	filter("configurations:Release")
		optimize("On")