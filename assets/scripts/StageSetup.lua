local Platforms = {}
local scripted = {}

function PlatformBehaviourVert(plat)
	while true do
		cpp_moveObject( plat, 600.0, 140.0, 5.0)
		coroutine.yield()
		cpp_moveObject(plat, 600.0, 600.0, 1.0)
		coroutine.yield()
	end
end

function IssueNextTask( plat)

	if coroutine.status(scripted[plat].behaviour) ~= 'dead' then
			coroutine.resume(scripted[plat].behaviour, Platforms[1])
	end
end



function LoadPlatforms(host, stageNum)

	if stageNum == 1 then
		Platform = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 300, 600)
		Platforms[1] = Platform
		scripted[Platforms[1]] = {behaviour = coroutine.create(PlatformBehaviourVert) }
		IssueNextTask( Platforms[1])
	end

end