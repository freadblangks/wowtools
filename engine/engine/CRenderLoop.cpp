#include "CRenderLoop.h"
#include "SMaterial.h"
#include "IRenderer.h"
#include "Engine.h"
#include "IVideoDriver.h"
#include "CCamera.h"

bool OpaqueCompare(const SRenderUnit* a, const SRenderUnit* b)
{
	const SGlobalLayerData& layerData1 = a->renderer->getGlobalLayerData();
	const SGlobalLayerData& layerData2 = b->renderer->getGlobalLayerData();

	if (layerData1 != layerData2)
		return layerData1 < layerData2;

	int queue1 = a->renderer->getRenderQueue();
	int queue2 = b->renderer->getRenderQueue();
	if (queue1 != queue2)
		return queue1 < queue2;

	ASSERT(queue1 >= ERQ_INDEX_MIN && queue1 <= ERQ_GEOMETRY_INDEX_MAX);

	//render all first passes first

	//lightmap index

	//shader
	if (a->shaderSortId != b->shaderSortId)
		return a->shaderSortId < b->shaderSortId;

	//material

	//pass

	if (a->distance != b->distance)
		return a->distance > b->distance;

	return &a < &b;
}

bool AfterOpaqueCompare(const SRenderUnit* a, const SRenderUnit* b)
{
	const SGlobalLayerData& layerData1 = a->renderer->getGlobalLayerData();
	const SGlobalLayerData& layerData2 = b->renderer->getGlobalLayerData();

	if (layerData1 != layerData2)
		return layerData1 < layerData2;

	int queue1 = a->renderer->getRenderQueue();
	int queue2 = b->renderer->getRenderQueue();
	if (queue1 != queue2)
		return queue1 < queue2;

	ASSERT(queue1 > ERQ_GEOMETRY_INDEX_MAX);

	if (a->distance != b->distance)
		return a->distance < b->distance;

	//render all first passes first

	//lightmap index

	//shader
	if (a->shaderSortId != b->shaderSortId)
		return a->shaderSortId < b->shaderSortId;

	//material

	//pass


	return &a < &b;
}

CRenderLoop::CRenderLoop()
{
	Driver = g_Engine->getDriver();
}

CRenderLoop::~CRenderLoop()
{

}

void CRenderLoop::addRenderUnit(const SRenderUnit* unit)
{
	int renderQueue = unit->renderer->getRenderQueue();

	if (renderQueue <= ERQ_GEOMETRY_INDEX_MAX)		//solid
	{
		m_RenderUnits_Opaque.push_back(unit);
	}
	else if (renderQueue <= ERQ_INDEX_MAX)		//transparent
	{
		m_RenderUnits_AfterOpaque.push_back(unit);
	}
}

void CRenderLoop::doRenderLoopPrepass(const CCamera* cam)
{

}

void CRenderLoop::doRenderLoopForward(const CCamera* cam)
{
	renderOpaques(cam);
	renderAfterOpaues(cam);
}

void CRenderLoop::clearRenderUnits()
{
	for (const SRenderUnit* unit : m_RenderUnits_Opaque)
	{
		delete unit;
	}
	m_RenderUnits_Opaque.clear();

	for (const SRenderUnit* unit : m_RenderUnits_AfterOpaque)
	{
		delete unit;
	}
	m_RenderUnits_AfterOpaque.clear();
}

void CRenderLoop::renderOpaques(const CCamera* cam)
{
	std::sort(m_RenderUnits_Opaque.begin(), m_RenderUnits_Opaque.end(), OpaqueCompare);

	const auto& matView = cam->getViewTM();
	const auto& matProjection = cam->getProjectionTM();

	for (const SRenderUnit* unit : m_RenderUnits_Opaque)
	{
		if (!unit->primCount)
			continue;

		const IRenderer* renderer = unit->renderer;

		Driver->setWorldViewProjection(renderer->getLocalToWorldMatrix(), matView, matProjection);

		Driver->setMaterial(renderer->getMaterial());
		Driver->setGlobalMaterial(Driver->getGlobalMaterial3D());

		Driver->draw(unit->vbuffer, unit->ibuffer, unit->primType, unit->primCount, unit->drawParam, cam->IsOrthogonal());
	}
}

void CRenderLoop::renderAfterOpaues(const CCamera* cam)
{
	std::sort(m_RenderUnits_AfterOpaque.begin(), m_RenderUnits_AfterOpaque.end(), AfterOpaqueCompare);
}
