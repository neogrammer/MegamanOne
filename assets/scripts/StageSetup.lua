Platforms = {}
scripted = {}
PlatformObject = nil
PlatformObject2 = nil

CurrentStage = {}
function PlatformBehaviourHoriz(plat)
	while true do
		cpp_moveObject( CurrentStage["host"], PlatformObject, 100.0, 850.0, 5.0)
		coroutine.yield()
		cpp_moveObject(CurrentStage["host"], PlatformObject, 600.0, 850.0, 5.0)
		coroutine.yield()
	end
end

function PlatformBehaviourVert(plat)
	while true do
		cpp_moveObjectUp( CurrentStage["host"], PlatformObject2, 50.0, 100.0, 1.0)
		coroutine.yield()
		cpp_moveObjectUp(CurrentStage["host"], PlatformObject2, 50.0, 500.0, 5.0)
		coroutine.yield()
	end
end

function IssueNextTask( plat)

	if coroutine.status(scripted[plat].behaviour) ~= 'dead' then
		if plat == PlatformObject then
			if PlatformObject2 ~= nil then
				if coroutine.status(scripted[PlatformObject2].behaviour) ~= 'suspended' or coroutine.status(scripted[PlatformObject2].behaviour) == 'normal' or coroutine.status(scripted[PlatformObject2].behaviour) == 'running' then
					cpp_retry( CurrentStage["host"], PlatformObject)	
				else
					coroutine.resume(scripted[PlatformObject].behaviour, PlatformObject)	
				end
			else
				coroutine.resume(scripted[PlatformObject].behaviour, PlatformObject)
			end
		elseif  plat == PlatformObject2 then
			if PlatformObject ~= nil then
				if coroutine.status(scripted[PlatformObject].behaviour) ~= 'suspended' or coroutine.status(scripted[PlatformObject].behaviour) == 'normal' or coroutine.status(scripted[PlatformObject].behaviour) == 'running' then
					cpp_retry( CurrentStage["host"], PlatformObject2)	
				else
					coroutine.resume(scripted[PlatformObject2].behaviour, PlatformObject2)
				end
			else
				coroutine.resume(scripted[PlatformObject2].behaviour, PlatformObject2)
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

		PlatformObject2 = cpp_createPlatform(host, 1, 0, 0, 67, 40, 0, 0, 67, 20, 50, 500)
		scripted[PlatformObject2] = {behaviour = coroutine.create(PlatformBehaviourVert) }
		IssueNextTask( PlatformObject2)
	end

end