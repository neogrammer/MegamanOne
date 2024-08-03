Platforms = {}
scripted = {}
PlatformObject = nil
PlatformObject2 = nil

CurrentStage = {}
function PlatformBehaviourHoriz(plat)
	while true do
		cpp_moveObject( CurrentStage["host"], plat, 100.0, 850.0, 5.0)
		coroutine.yield()
		cpp_moveObject(CurrentStage["host"], plat, 600.0, 850.0, 5.0)
		coroutine.yield()
	end
end

function PlatformBehaviourVert(plat2)
	while true do
		cpp_moveObjectUp( CurrentStage["host"], plat2, 350.0, 100.0, 1.0)
		coroutine.yield()
		cpp_moveObjectUp(CurrentStage["host"], plat2, 350.0, 600.0, 7.0)
		coroutine.yield()
	end
end

function IssueNextTask(aplat)

	if coroutine.status(scripted[aplat].behaviour) ~= 'dead' then
		if aplat == PlatformObject then
			if PlatformObject2 ~= nil then
				if coroutine.status(scripted[PlatformObject2].behaviour) ~= 'suspended' then
					cpp_retry( CurrentStage["host"], aplat)	
				else
					coroutine.resume(scripted[aplat].behaviour, aplat)	
				end
			else
				coroutine.resume(scripted[aplat].behaviour, aplat)
			end
		elseif  aplat == PlatformObject2 then
			if PlatformObject ~= nil then
				if coroutine.status(scripted[PlatformObject].behaviour) ~= 'suspended' then
					cpp_retry( CurrentStage["host"], aplat)	
				else
					coroutine.resume(scripted[aplat].behaviour, aplat)
				end
			else
				coroutine.resume(scripted[aplat].behaviour, aplat)
			end
		end
	end

end



function LoadPlatforms(host, stageNum)
	CurrentStage["host"] = host
	if stageNum == 1 then
		PlatformObject = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 600, 850)
		scripted[PlatformObject] = {behaviour = coroutine.create(PlatformBehaviourHoriz) }
		IssueNextTask( PlatformObject)

		PlatformObject2 = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 350, 600)
		scripted[PlatformObject2] = {behaviour = coroutine.create(PlatformBehaviourVert) }
		IssueNextTask( PlatformObject2)
	end

end