project "nlohmann"
    kind "StaticLib"
    language "c++"
    cppdialect "C++23"
    location "./"

    files {
        "include/nlohmann/*.hpp",
        "json.cpp"
    }

    includedirs {
        "include"
    }

    vpaths {
        ["Header Files/*"] = { "include/nlohmann/*.h" },
        ["Source Files/*"] = { "json.cpp" },
    }

    filter("configurations:Debug")
		symbols("On")

	filter("configurations:Release")
		optimize("On")