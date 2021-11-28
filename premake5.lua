workspace "Renderer"
	configurations {"Debug", "Release" , "Debug_all"}
	
	system "Windows"
	architecture "x64"
	
	
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
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		location "build/%{prj.name}"
		
		
		targetdir ("bin/output/" .. "%{cfg.buildcfg}")
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		files {"src/**.cpp","src/**.h", "src/**.hpp",
				"include/**.h", "include/**.hpp",
				"thirdparty/src/**.c" ,"thirdparty/src/**.cpp" }
				
		includedirs{"./include" , "./src" , "./thirdparty/include" , "./thirdparty/glm/glm"}
		libdirs {"thirdparty/libs/"}
		links {"glfw3"}