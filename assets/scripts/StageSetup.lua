Platforms = {}

function LoadPlatforms(host, stageNum)

	if stageNum == 1 then
		Platform = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 300, 600)
		Platforms[1] = Platform
	end

end