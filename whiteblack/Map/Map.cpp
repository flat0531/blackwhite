#include "Map.h"


struct P
{
	Vec2f po, si;

	P(Vec2f po, Vec2f si) :
		po(po),
		si(si)
	{

	}
};

P p(Vec2f::Zero(), Vec2f::Zero());

Map::Map(){

}

void Map::update(){

}

void Map::draw(){

	for (int y = 0; y < static_cast<int>(map_chip.size()); y++)
	{
		for (int x = 0; x < static_cast<int>(map_chip[y].size()); x++)
		{
			map_chip[y][x]->draw();

		}
	}

	drawBox(p.po.x(), p.po.y(), p.si.x(), p.si.y(), 10, Color::green);
}

void Map::setup(int stage){

	std::string file_name = "res/map/stage" + std::to_string(stage) + ".txt";
	std::ifstream* map_file = new std::ifstream(file_name);

	assert(!map_file->fail());

	Vec2i map_size;

	*map_file >> map_size.y();
	*map_file >> map_size.x();


	std::vector<BlockBase*> map_chip_;
	int type;
	int c = 0;
	for (int y = 0; y < map_size.y(); y++)
	{
		std::cout << std::endl;
		for (int x = 0; x < map_size.x(); x++)
		{
			c++;
			*map_file >> type;

			switch (type)
			{
			case 0:
				map_chip_.push_back(new BlockBase);
				map_chip_[x]->setCondition(CONDITION::NONE);
				break;

			case 1:
				map_chip_.push_back(new NormalBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/normal_block.png"));
				map_chip_[x]->setCondition(CONDITION::STRIPE);
				break;

			case 2:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_right_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				map_chip_[x]->setVec(Vec2f(-10.0f, 0.0f));
				break;

			case 3:
				map_chip_.push_back(new FallBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/fall_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				map_chip_[x]->setVec(Vec2f(0.0f, -10.0f));
				break;

			case 4:
				map_chip_.push_back(new DoubleBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/double_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				break;

			case 5:
				map_chip_.push_back(new NormalBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				break;

			case 6:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_right_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				map_chip_[x]->setVec(Vec2f(-10.0f, 0.0f));
				break;

			case 7:
				map_chip_.push_back(new FallBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/fall_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				map_chip_[x]->setVec(Vec2f(0.0f, -10.0f));
				break;

			case 8:
				map_chip_.push_back(new DoubleBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/double_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				break;

			case 9:
				map_chip_.push_back(new NormalBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/normal_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				break;

			case 10:
				map_chip_.push_back(new BlockBase);
				map_chip_[x]->setCondition(CONDITION::NONE);
				player_start_pos = Vec2f(
					static_cast<float>(BLOCKSIZE::WIDTH)*x,
					-(static_cast<float>(BLOCKSIZE::HEIGHT)*y));
				continue;

			case 11:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_down_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				map_chip_[x]->setVec(Vec2f(0.0f, -10.0f));
				break;

			case 12:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_left_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				map_chip_[x]->setVec(Vec2f(10.0f, 0.0f));
				break;

			case 13:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_up_white_block.png"));
				map_chip_[x]->setCondition(CONDITION::WHITE);
				map_chip_[x]->setVec(Vec2f(0.0f, 10.0f));
				break;

			case 14:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_down_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				map_chip_[x]->setVec(Vec2f(0.0f, -10.0f));
				break;

			case 15:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_left_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				map_chip_[x]->setVec(Vec2f(-10.0f, 0.0f));
				break;

			case 16:
				map_chip_.push_back(new MoveBlock);
				//map_chip_[x]->setImage(Texture("res/Texture/move_up_black_block.png"));
				map_chip_[x]->setCondition(CONDITION::BLACK);
				map_chip_[x]->setVec(Vec2f(0.0f, 10.0f));
				break;
			}

			map_chip_[x]->setPos(Vec2f(
				static_cast<float>(BLOCKSIZE::WIDTH)*x,
				-(static_cast<float>(BLOCKSIZE::HEIGHT)*y)));
		}

		map_chip.push_back(map_chip_);

		map_chip_.clear();
	}




	delete map_file;
}

Vec2f Map::getPlayerStartPos() const{
	return player_start_pos;
}

Vec2f Map::isHitPlayerToBlock(Object player, CONDITION player_condition){

	p.po = player.pos;
	p.si = player.size;

	Vec2f sinking = Vec2f::Zero();

	for (int y = 0; y < static_cast<int>(map_chip.size()); y++)
	{
		for (int x = 0; x < static_cast<int>(map_chip[y].size()); x++)
		{
			if (map_chip[y][x]->getCondition() == CONDITION::NONE)
				continue;

			//top
			if (map_chip[y][x]->getCondition() != map_chip[y - (1 * (y != 0))][x]->getCondition())
			{
				if (player.pos.x() + player.size.x() > map_chip[y][x]->getPos().x() &&
					player.pos.x() < map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x())
				{
					if (player.pos.y() > map_chip[y][x]->getPos().y() + map_chip[y][x]->getSize().y() - 50.0f &&
						player.pos.y() < map_chip[y][x]->getPos().y() + map_chip[y][x]->getSize().y())
					{
						if (player_condition == map_chip[y][x]->getCondition())
							return Vec2f(0.0f, 0.0f);

						if (player.vec.y() < 0.0f)
						{
							sinking.y() = map_chip[y][x]->getPos().y() + map_chip[y][x]->getSize().y() - player.pos.y();

							if (map_chip[y][x]->getStatus() == BLOCK::FALL)
								map_chip[y][x]->setFallFlag(true);
						}
					}
				}
			}

			//left
			if (map_chip[y][x]->getCondition() != map_chip[y][x - (1 * (x != 0))]->getCondition())
			{
				if (player.pos.x() + player.size.x() > map_chip[y][x]->getPos().x() &&
					player.pos.x() + player.size.x() < map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x() / 2)
				{
					if (player.pos.y() + player.size.y() > map_chip[y][x]->getPos().y() &&
						player.pos.y() < map_chip[y][x]->getPos().y() + map_chip[y][x]->getSize().y())
					{
						if (player_condition == map_chip[y][x]->getCondition())
							return Vec2f(0.0f, 0.0f);

						sinking.x() = map_chip[y][x]->getPos().x() - (player.pos.x() + player.size.x());
					}
				}
			}

			//right
			if (map_chip[y][x]->getCondition() != map_chip[y][x + (1 * (map_chip[y].size()-1 != x))]->getCondition())
			{
				if (player.pos.x() > map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x() / 2 &&
					player.pos.x() < map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x())
				{
					if (player.pos.y() + player.size.y() > map_chip[y][x]->getPos().y() &&
						player.pos.y() < map_chip[y][x]->getPos().y() + map_chip[y][x]->getSize().y())
					{
						if (player_condition == map_chip[y][x]->getCondition())
							return Vec2f(0.0f, 0.0f);

						sinking.x() = (map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x())- player.pos.x();
					}
				}
			}

			//down
			if (map_chip[y][x]->getCondition() != map_chip[y + (1 * (map_chip.size()-1 != y))][x]->getCondition())
			{
				if (player.pos.x() + player.size.x() > map_chip[y][x]->getPos().x() &&
					player.pos.x() < map_chip[y][x]->getPos().x() + map_chip[y][x]->getSize().x())
				{
					if (player.pos.y() + player.pos.y() > map_chip[y][x]->getPos().y() &&
						player.pos.y() + player.pos.y() < map_chip[y][x]->getPos().y() + 50.0f)
					{
						if (player_condition == map_chip[y][x]->getCondition())
							return Vec2f(0.0f, 0.0f);

						if (player.vec.y() > 0.0f)
						{
							sinking.y() = map_chip[y][x]->getPos().y() - (player.pos.y() + player.size.y());
						}
					}
				}
			}

		}
	}

	return sinking;
}

void Map::isHitMoveBlockToBlock()
{
	for (int y = 0; y < static_cast<int>(map_chip.size()); y++)
	{
		for (int x = 0; x < static_cast<int>(map_chip[y].size()); x++)
		{
			if (map_chip[y][x]->getStatus() != BLOCK::MOVE)
				continue;

			if (map_chip[y][x]->getMoveFlag() == true)
			{
				BlockBase* move_block = map_chip[y][x];

				for (int y1 = 0; y1 < static_cast<int>(map_chip.size()); y1++)
				{
					for (int x1 = 0; x1 < static_cast<int>(map_chip[y].size()); x1++)
					{
						if (map_chip[y1][x1]->getCondition() == CONDITION::NONE)
							continue;

						//���ړ�
						if (move_block->getVectol().x() < 0.0f)
						{
							if (move_block->getPos().x() < map_chip[y][x1]->getPos().x() + map_chip[y][x1]->getSize().x())
							{
								move_block->setPos(Vec2f(map_chip[y][x1]->getPos().x() + map_chip[y][x1]->getSize().x(), move_block->getPos().y()));
								move_block->setMoveFlag(false);
							}
						}

						//�E�ړ�
						if (move_block->getVectol().x() > 0.0f)
						{
							if (move_block->getPos().x() + move_block->getSize().x() > map_chip[y][x1]->getPos().x())
							{
								move_block->setPos(Vec2f(map_chip[y][x1]->getPos().x() - move_block->getSize().x(), move_block->getPos().y()));
								move_block->setMoveFlag(false);
							}
						}

						//��ړ�
						if (move_block->getVectol().y() > 0.0f)
						{
							if (move_block->getPos().y() + move_block->getSize().y() > map_chip[y1][x]->getPos().y())
							{
								move_block->setPos(Vec2f(move_block->getPos().x(), map_chip[y1][x]->getPos().y() - move_block->getSize().y()));
								move_block->setMoveFlag(false);
							}
						}

						//���ړ�
						if (move_block->getVectol().y() < 0.0f)
						{
							if (move_block->getPos().y() < map_chip[y1][x]->getPos().y() + map_chip[y1][x]->getSize().y())
							{
								move_block->setPos(Vec2f(move_block->getPos().x(), map_chip[y1][x]->getPos().y() + map_chip[y1][x]->getSize().y()));
								move_block->setMoveFlag(false);
							}
						}
					}
				}
			}
		}
	}
}

void Map::selected(Vec2i selected_pos){

	drawBox(selected_pos.x() * static_cast<float>(BLOCKSIZE::WIDTH),
		-selected_pos.y() * static_cast<float>(BLOCKSIZE::HEIGHT),
		static_cast<float>(BLOCKSIZE::WIDTH),
		static_cast<float>(BLOCKSIZE::HEIGHT),
		10,
		Color::yellow);
}

bool Map::sucked(Vec2i selected_pos){

	switch (map_chip[selected_pos.y()][selected_pos.x()]->getStatus())
	{
	case BLOCK::NORMAL:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::BLACK)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::WHITE);
		return true;

	case BLOCK::MOVE:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::BLACK)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::WHITE);
		if (map_chip[selected_pos.y()][selected_pos.x()]->getMoveFlag() == false)
			map_chip[selected_pos.y()][selected_pos.x()]->setMoveFlag(true);
		else
			map_chip[selected_pos.y()][selected_pos.x()]->setMoveFlag(false);
		return true;

	case BLOCK::FALL:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::BLACK)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::WHITE);
		map_chip[selected_pos.y()][selected_pos.x()]->setFallFlag(true);
		return true;

	case BLOCK::DOUBLE:
		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::WHITE);
		return true;
	}

	return false;
}

bool Map::released(Vec2i selected_pos)
{
	switch (map_chip[selected_pos.y()][selected_pos.x()]->getStatus())
	{
	case BLOCK::NORMAL:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::WHITE)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::BLACK);
		return true;

	case BLOCK::MOVE:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::WHITE)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::BLACK);
		if (map_chip[selected_pos.y()][selected_pos.x()]->getMoveFlag() == false)
			map_chip[selected_pos.y()][selected_pos.x()]->setMoveFlag(true);
		else
			map_chip[selected_pos.y()][selected_pos.x()]->setMoveFlag(false);
		return true;

	case BLOCK::FALL:
		if (map_chip[selected_pos.y()][selected_pos.x()]->getCondition() != CONDITION::WHITE)
			return false;

		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::BLACK);
		map_chip[selected_pos.y()][selected_pos.x()]->setFallFlag(true);
		return true;

	case BLOCK::DOUBLE:
		map_chip[selected_pos.y()][selected_pos.x()]->setCondition(CONDITION::BLACK);
		return true;
	}

	return false;
}

void Map::mapDelete()
{
	map_chip.clear();
}