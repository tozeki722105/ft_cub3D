#include <gtest/gtest.h>
#include "parse.h"

class TestPath
{
	private:
		std::string north_path_;
		std::string south_path_;
		std::string west_path_;
		std::string east_path_;
	
	public:
  const std::string &getNorthPath();
  const std::string &getSouthPath();
  const std::string &getWestPath();
  const std::string &getEastPath();
  void setNorthPath(std::string first_name);
  void setSouthPath(std::string first_name);
  void setWestPath(std::string first_name);
  void setEastPath(std::string first_name);
};

const std::string &TestPath::getNorthPath() { return north_path_; }

const std::string &TestPath::getSouthPath() { return south_path_; }

const std::string &TestPath::getWestPath() { return west_path_; }

const std::string &TestPath::getEastPath() { return east_path_; }

void TestPath::setNorthPath(std::string north_path) { north_path_ = north_path; }

void TestPath::setSouthPath(std::string south_path) { south_path_ = south_path ;}

void TestPath::setWestPath(std::string west_path) { west_path_ = west_path; }

void TestPath::setEastPath(std::string east_path) { east_path_ = east_path; }


// Demonstrate some basic assertions.
TEST(parseTest, BasicAssertions) {
  // Expect equality.
	//
	std::cout << "==== ok_subject.cub =====" << std::endl;
	char *path = "./map/ok_basic.cub";
  t_loader actual = parse(path);

	TestPath test;	
	test.setNorthPath("./img/text_n.xpm");
	test.setSouthPath("./img/text_s.xpm");
	test.setWestPath("./img/text_w.xpm");
	test.setEastPath("./img/text_e.xpm");

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_corner_space.cub ====" << std::endl;
	path = "./map/ok_corner_space.cub";

	test.setNorthPath("./img/collect.xpm");
	test.setSouthPath("./img/exit.xpm");
	test.setWestPath("./img/tile.xpm");
	test.setEastPath("./img/wall.xpm");
  actual = parse(path);
  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_divide_map.cub ====" << std::endl;
	path = "./map/ok_devide_map.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_mini.cub ====" << std::endl;
	path = "./map/ok_mini.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_nl_down.cub ====" << std::endl;
	path = "./map/ok_nl_down.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_nl_up.cub ====" << std::endl;
	path = "./map/ok_nl_up.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_squea.cub ====" << std::endl;
	path = "./map/ok_squea.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== ok_subject ====" << std::endl;
	path = "./map/ok_subject.cub";
  actual = parse(path);

  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

	std::cout << "==== err1_no_map.cub ====" << std::endl;
	path = "./map/err1_no_map.cub";

  /* EXPECT_STREQ(parse(path), "Missing map data"); */
  //int 
  /* EXPECT_EQ(actual.floor_color, 14443520); */
  /* EXPECT_EQ(actual.ceiling_color, 14753280); */
  /* EXPECT_EQ(actual.map_x_count, 33); */
  /* EXPECT_EQ(actual.map_y_count, 14); */

  //double
}
