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
TEST(ParseTest, BasicAssertions) {
  // Expect equality.
	TestPath test;	
	test.setNorthPath("./img/collect.xpm");
	test.setSouthPath("./img/exit.xpm");
	test.setWestPath("./img/title.xpm");
	test.setEastPath("./img/wall.xpm");

	char *path = "../map/test_subject.cub";
  t_loader actual = parse(path);
  // cahr *
  EXPECT_STREQ(actual.north_path, test.getNorthPath().c_str());
  EXPECT_STREQ(actual.south_path, test.getSouthPath().c_str());
  EXPECT_STREQ(actual.west_path, test.getWestPath().c_str());
  EXPECT_STREQ(actual.east_path, test.getEastPath().c_str());

  //int 
  EXPECT_EQ(actual.floor_color, 14443520);
  EXPECT_EQ(actual.ceiling_color, 14753280);
  EXPECT_EQ(actual.map_x_count, 33);
  EXPECT_EQ(actual.map_y_count, 14);

  //double
}
