Platforms = {}
scripted = {}
PlatformObject = nil
CurrentStage = {}
function PlatformBehaviourVert(plat)
	while true do
		cpp_moveObject( CurrentStage["host"], PlatformObject, 100.0, 850.0, 5.0)
		coroutine.yield()
		cpp_moveObject(CurrentStage["host"], PlatformObject, 600.0, 850.0, 5.0)
		coroutine.yield()
	end
end

function IssueNextTask( plat)

	if coroutine.status(scripted[PlatformObject].behaviour) ~= 'dead' then
			coroutine.resume(scripted[PlatformObject].behaviour, PlatformObject)
	end
end



function LoadPlatforms(host, stageNum)
	CurrentStage["host"] = host
	if stageNum == 1 then
		PlatformObject = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 600, 850)
		scripted[PlatformObject] = {behaviour = coroutine.create(PlatformBehaviourVert) }
		IssueNextTask( PlatformObject)
	end

end