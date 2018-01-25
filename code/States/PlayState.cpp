#include "PlayState.h"

#include "../Graphics/FrameBuffers/GameRenderer.h"


PlayState::PlayState() :
playerCamera({2.0f, 2.0f})
{
	/*std::vector<Sector> sectors;
	Sector sector1(-0.7f, 1.7f);
	Sector sector2(-1.0f, 1.0f);

	sector1.setFloorTex("greystone");
	sector1.setCeilingTex("greystone");

	sector2.setFloorTex("greystone");
	sector2.setCeilingTex("greystone");

	sector1.addWall({{1, 1}, {2, 1}});
	sector1.addWall({{2, 1}, {3, 2}});
	sector1.addWall({{3, 2}, {3, 3}, &sector2});
	sector1.addWall({{3, 3}, {2, 4}});
	sector1.addWall({{2, 4}, {1, 4}});
	sector1.addWall({{1, 4}, {1, 1}});

	sector1.setWallTopTexCoords(2, 0.0f, 2.0f, 0.0f, 0.3f);
	sector1.setWallMiddleTexture(0, "eagle");
	sector1.setWallMiddleTexture(1, "eagle");
	sector1.setWallTopTexture(2, "eagle");
	sector1.setWallMiddleTexture(3, "eagle");
	sector1.setWallMiddleTexture(4, "eagle");
	sector1.setWallMiddleTexture(5, "eagle");

	sector2.addWall({{4, 1}, {5, 1}});
	sector2.addWall({{5, 1}, {5, 4}});
	sector2.addWall({{5, 4}, {4, 4}});
	sector2.addWall({{4, 4}, {4, 3}});
	sector2.addWall({{4, 3}, {3, 3}});
	sector2.addWall({{3, 3}, {3, 2}, &sector1});
	sector2.addWall({{3, 2}, {4, 2}});
	sector2.addWall({{4, 2}, {4, 1}});

	sector2.setWallMiddleTexture(0, "eagle");
	sector2.setWallMiddleTexture(1, "eagle");
	sector2.setWallMiddleTexture(2, "eagle");
	sector2.setWallMiddleTexture(3, "eagle");
	sector2.setWallMiddleTexture(4, "eagle");
	sector2.setWallBottomTexture(5, "eagle");
	sector2.setWallMiddleTexture(6, "eagle");
	sector2.setWallMiddleTexture(7, "eagle");

	sectors.push_back(sector1);
	sectors.push_back(sector2);

	bspTree.loadBspTree(sectors);*/

	Sector sec1(-1.0f, 5.0f);

	sec1.setCeilingTex("sky");
	sec1.setFloorTex("grass");

	Sector sec2(-0.8f, 2.0f);

	sec2.setCeilingTex("brown_brick");
	sec2.setFloorTex("stone_brick");

	Sector sec3(-0.6f, 2.0f);

	sec3.setFloorTex("stone_brick");
	sec3.setCeilingTex("brown_brick");

	Sector sec4(-0.4f, 2.0f);

	sec4.setFloorTex("stone_brick");
	sec4.setCeilingTex("brown_brick");

	Sector sec5(-0.2f, 2.0f);

	sec5.setFloorTex("stone_brick");
	sec5.setCeilingTex("brown_brick");

	Sector sec6(0.0f, 2.0f);

	sec6.setFloorTex("red_carpet");
	sec6.setCeilingTex("brown_brick");

	Sector sec7(0.0f, 2.0f);

	sec7.setFloorTex("red_carpet");
	sec7.setCeilingTex("brown_brick");

	Sector sec8(0.0f, 2.0f);

	sec8.setFloorTex("red_carpet");
	sec8.setCeilingTex("stone_brick");

	sec1.addWall({{-1, 1}, { 0,-1}});
	sec1.addWall({{ 0,-1}, { 3, 0}});
	sec1.addWall({{ 3, 0}, { 3, 2}});
	sec1.addWall({{ 3, 2}, { 2, 3}});
	sec1.addWall({{ 2, 3}, { 1, 2}});
	sec1.addWall({{ 1, 2}, { 0, 2}});
	sec1.addWall({{ 0, 2}, {-1, 1}});
	sec1.addWall({{ 0, 0}, { 0, 1}});
	sec1.addWall({{ 0, 1}, { 1, 0}});
	sec1.addWall({{ 1, 0}, { 0, 0}});

	sec1.getWall(5).setNeighbour(&sec2);
	sec1.getWall(0).setNeighbour(&sec8);

	sec1.setWallBottomTexture(0, "brown_brick");
	sec1.setWallBottomTexCoords(0, 0.0f, 2.0f, 0.05f, 0.4f);
	sec1.setWallTopTexCoords(0, 0.0f, 2.0f, 0.0f, 1.0f);
	sec1.setWallTopTexture(0, "brown_brick");
	sec1.setWallMiddleTexture(1, "brown_brick");
	sec1.setWallMiddleTexCoords(1, 0.0f, 3.0f, 0.0f, 2.0f);
	sec1.setWallMiddleTexture(2, "brown_brick");
	sec1.setWallMiddleTexCoords(2, 0.0f, 1.5f, 0.0f, 2.0f);
	sec1.setWallMiddleTexture(3, "brown_brick");
	sec1.setWallMiddleTexCoords(3, 0.0f, 1.0f, 0.0f, 2.0f);
	sec1.setWallMiddleTexture(4, "brown_brick");
	sec1.setWallMiddleTexCoords(4, 0.0f, 1.0f, 0.0f, 2.0f);
	sec1.setWallTopTexture(5, "brown_brick");
	sec1.setWallBottomTexture(5, "stone_brick");
	sec1.setWallBottomTexCoords(5, 0.0f, 1.0f, 0.0f, 0.1f);
	sec1.setWallMiddleTexture(6, "brown_brick");
	sec1.setWallMiddleTexCoords(6, 0.0f, 1.0f, 0.0f, 2.0f);

	sec1.setWallMiddleTexture(7, "planks");
	sec1.setWallMiddleTexture(8, "planks");
	sec1.setWallMiddleTexture(9, "planks");

	sec2.addWall({{ 0, 2.25f}, { 0, 2}});
	sec2.addWall({{ 0, 2}, { 1, 2}});
	sec2.addWall({{ 1, 2}, { 1, 2.25f}});
	sec2.addWall({{ 1, 2.25f}, { 0, 2.25f}});

	sec2.setWallMiddleTexture(0, "brown_brick");
	sec2.setWallMiddleTexCoords(0, 0.0f, 0.2f, 0.0f, 0.95f);
	sec2.setWallMiddleTexture(2, "brown_brick");
	sec2.setWallMiddleTexCoords(2, 0.0f, 0.2f, 0.0f, 0.95f);
	sec2.setWallBottomTexture(3, "stone_brick");
	sec2.setWallBottomTexCoords(3, 0.0f, 1.0f, 0.0f, 0.1f);

	sec2.getWall(1).setNeighbour(&sec1);
	sec2.getWall(3).setNeighbour(&sec3);

	sec3.addWall({{ 0, 2.5f}, { 0, 2.25f}});
	sec3.addWall({{ 0, 2.25f}, { 1, 2.25f}});
	sec3.addWall({{ 1, 2.25f}, { 1, 2.5f}});
	sec3.addWall({{ 1, 2.5f}, { 0, 2.5f}});

	sec3.setWallMiddleTexture(0, "brown_brick");
	sec3.setWallMiddleTexCoords(0, 0.0f, 0.2f, 0.0f, 0.90f);
	sec3.setWallMiddleTexture(2, "brown_brick");
	sec3.setWallMiddleTexCoords(2, 0.0f, 0.2f, 0.0f, 0.90f);
	sec3.setWallBottomTexture(3, "stone_brick");
	sec3.setWallBottomTexCoords(3, 0.0f, 1.0f, 0.0f, 0.1f);

	sec3.getWall(1).setNeighbour(&sec2);
	sec3.getWall(3).setNeighbour(&sec4);

	sec4.addWall({{ 0, 2.75f}, { 0, 2.5f}});
	sec4.addWall({{ 0, 2.5f}, { 1, 2.5f}});
	sec4.addWall({{ 1, 2.5f}, { 1, 2.75f}});
	sec4.addWall({{ 1, 2.75f}, { 0, 2.75f}});

	sec4.setWallMiddleTexture(0, "brown_brick");
	sec4.setWallMiddleTexCoords(0, 0.0f, 0.2f, 0.0f, 0.83f);
	sec4.setWallMiddleTexture(2, "brown_brick");
	sec4.setWallMiddleTexCoords(2, 0.0f, 0.2f, 0.0f, 0.83f);
	sec4.setWallBottomTexture(3, "stone_brick");
	sec4.setWallBottomTexCoords(3, 0.0f, 1.0f, 0.0f, 0.1f);

	sec4.getWall(1).setNeighbour(&sec3);
	sec4.getWall(3).setNeighbour(&sec5);

	sec5.addWall({{ 0, 3}, { 0, 2.75f}});
	sec5.addWall({{ 0, 2.75f}, { 1, 2.75f}});
	sec5.addWall({{ 1, 2.75f}, { 1, 3}});
	sec5.addWall({{ 1, 3}, { 0, 3}});

	sec5.setWallMiddleTexture(0, "brown_brick");
	sec5.setWallMiddleTexCoords(0, 0.0f, 0.2f, 0.0f, 0.77f);
	sec5.setWallMiddleTexture(2, "brown_brick");
	sec5.setWallMiddleTexCoords(2, 0.0f, 0.2f, 0.0f, 0.77f);
	sec5.setWallBottomTexture(3, "stone_brick");
	sec5.setWallBottomTexCoords(3, 0.0f, 1.0f, 0.0f, 0.1f);

	sec5.getWall(1).setNeighbour(&sec4);
	sec5.getWall(3).setNeighbour(&sec6);

	sec6.addWall({{ 0, 3}, { 1, 3}});
	sec6.addWall({{ 1, 3}, { 1, 4}});
	sec6.addWall({{ 1, 4}, {-2, 4}});
	sec6.addWall({{-2, 4}, {-2, 2}});
	sec6.addWall({{-2, 2}, {-1, 2}});
	sec6.addWall({{-1, 2}, {-1, 3}});
	sec6.addWall({{-1, 3}, { 0, 3}});

	sec6.setWallMiddleTexture(1, "brown_brick");
	sec6.setWallMiddleTexCoords(1, 0.0f, 1.0f, 0.0f, 0.7f);
	sec6.setWallMiddleTexture(2, "brown_brick");
	sec6.setWallMiddleTexCoords(2, 0.0f, 3.0f, 0.0f, 0.7f);
	sec6.setWallMiddleTexture(3, "brown_brick");
	sec6.setWallMiddleTexCoords(3, 0.0f, 2.0f, 0.0f, 0.7f);
	sec6.setWallMiddleTexture(5, "brown_brick");
	sec6.setWallMiddleTexCoords(5, 0.0f, 1.0f, 0.0f, 0.7f);
	sec6.setWallMiddleTexture(6, "brown_brick");
	sec6.setWallMiddleTexCoords(6, 0.0f, 1.0f, 0.0f, 0.7f);

	sec6.getWall(0).setNeighbour(&sec5);
	sec6.getWall(4).setNeighbour(&sec7);

	sec7.addWall({{-1, 2}, {-2, 2}});
	sec7.addWall({{-2, 2}, {-3, 0}});
	sec7.addWall({{-3, 0}, {-2, 0}});
	sec7.addWall({{-2, 0}, {-1, 2}});

	sec7.setWallMiddleTexture(1, "brown_brick");
	sec7.setWallMiddleTexCoords(1, 0.0f, 2.5f, 0.0f, 0.7f);
	sec7.setWallMiddleTexture(3, "brown_brick");
	sec7.setWallMiddleTexCoords(3, 0.0f, 2.5f, 0.0f, 0.7f);

	sec7.getWall(0).setNeighbour(&sec6);
	sec7.getWall(2).setNeighbour(&sec8);

	sec8.addWall({{-2, 0}, {-3, 0}});
	sec8.addWall({{-3, 0}, {-4,-3}});
	sec8.addWall({{-4,-3}, { 0,-3}});
	sec8.addWall({{ 0,-3}, { 0,-1}});
	sec8.addWall({{ 0,-1}, {-1, 1}});
	sec8.addWall({{-1, 1}, {-2, 0}});

	sec8.setWallMiddleTexture(1, "brown_brick");
	sec8.setWallMiddleTexCoords(1, 0.0f, 2.5f, 0.0f, 0.7f);
	sec8.setWallMiddleTexture(2, "brown_brick");
	sec8.setWallMiddleTexCoords(2, 0.0f, 3.0f, 0.0f, 0.7f);
	sec8.setWallMiddleTexture(3, "brown_brick");
	sec8.setWallMiddleTexCoords(3, 0.0f, 1.5f, 0.0f, 0.7f);
	sec8.setWallMiddleTexture(5, "brown_brick");
	sec8.setWallMiddleTexCoords(5, 0.0f, 1.0f, 0.0f, 0.7f);

	sec8.getWall(0).setNeighbour(&sec7);
	sec8.getWall(4).setNeighbour(&sec1);

	std::vector<Sector> sectors;
	sectors.push_back(sec1);
	sectors.push_back(sec2);
	sectors.push_back(sec3);
	sectors.push_back(sec4);
	sectors.push_back(sec5);
	sectors.push_back(sec6);
	sectors.push_back(sec7);
	sectors.push_back(sec8);

	bspTree.loadBspTree(sectors);
}

void PlayState::update(float delta)
{
	playerCamera.setCurrentSector(bspTree.findSector(playerCamera.getPosition()));
	playerCamera.update(delta);
	bspTree.collideWithMap(playerCamera);
}

void PlayState::render(GameRenderer& renderer)
{
	renderer.resetScanLineAndBuffers();
	bspTree.drawBspTree(
			renderer,
			playerCamera);
}
