workspace "Renderer"
	configurations {"Debug", "Release" , "Debug_all"}
	
	system "Windows"
	architecture "x64"
	
	startproject "Application"
	
	filter {"configurations:Debug_all"}
		defines {	"RENDERER_DEBUG", "RENDERER_DEBUG_ALL"}
		optimize "Off"
		symbols "On"
		runtime "Debug"
	
	filter {"configurations:Debug"}
		defines {"RENDERER_DEBUG"}
		optimize "Debug"
		symbols "On"
		runtime "Release"
		
	filter {"configurations:Release"}
		defines {"RENDERER_RELEASE"}
		optimize "Full"
		symbols "Off"
		runtime "Release"
		
project "Renderer"
		kind "StaticLib"
		language "C++"
		cppdialect "C++20"
		location "build/%{prj.name}"
		warnings "Extra"
		
		flags {"FatalWarnings"}
		targetdir ("bin/output/" .. "%{cfg.buildcfg}")
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		files {"%{prj.name}/src/**.cpp","%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp",
				"%{prj.name}/include/**.h", "%{prj.name}/include/**.hpp",
				"thirdparty/src/**.c" ,"thirdparty/src/**.cpp" }
				
		includedirs{"%{prj.name}./include" , "%{prj.name}./src" , "./thirdparty/include" , "./thirdparty/glm/glm"}
		libdirs {"thirdparty/libs/"}
		links {"glfw3"}
		
		postbuildcommands {
			"{copy} ../../bin/output/%{cfg.buildcfg}/%{prj.name}.lib  ../../bin/output/%{cfg.buildcfg}/Test/",
			"{echo} Renderer Lib copied"
		}
		
project "Application"

		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		location "build/%{prj.name}"
		warnings "Extra"
		flags {"FatalWarnings"}
		targetdir ("bin/output/" .. "%{cfg.buildcfg}")
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		files {"%{prj.name}/src/**.cpp","%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp",
				"%{prj.name}/include/**.h", "%{prj.name}/include/**.hpp"}
				
		includedirs{".%{prj.name}/include" , "%{prj.name}./src", "./Renderer/include", "./thirdparty/include","./thirdparty/glm/glm"}
		links {"Renderer"}
		
		

project "GTest"
		kind "StaticLib"
		
		targetdir ("bin/output/" .. "%{cfg.buildcfg}" .. "/Test")
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		files { "googletest/googletest/src/gtest-all.cc" }
		includedirs { "googletest/googletest/include", "googletest/googletest" }

project "Application_gtest"

		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		location "build/%{prj.name}"
		
		targetdir ("bin/output/" .. "%{cfg.buildcfg}" .. "/Test")
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		files {"%{prj.name}/src/**.cpp","%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp",
				"%{prj.name}/include/**.h", "%{prj.name}/include/**.hpp"}
				
		includedirs{".%{prj.name}/include" , "%{prj.name}./src", "./Renderer/include", "./thirdparty/include","./thirdparty/glm/glm", "googletest/googletest/include"}
		links {"Renderer" ,"GTest"}
		