#include <gtest/gtest.h>
#include "parse.h"

// Demonstrate some basic assertions.
TEST(ParseTest, BasicAssertions) {
  // Expect equality.
	char *path = "../map/test_subject.cub";
  t_loader actual = parse(path);
  // cahr *
  EXPECT_STREQ(actual.north_path, "./img/collect.xpm");
  EXPECT_STREQ(actual.south_path, "./img/exit.xpm");
  EXPECT_STREQ(actual.west_path, "./img/tile.xpm");
  EXPECT_STREQ(actual.east_path, "./img/wall.xpm");

  //int 
  EXPECT_EQ(actual.floor_color, 14443520);
  EXPECT_EQ(actual.ceiling_color, 14753280);
  EXPECT_EQ(actual.map_x_count, 33);
  EXPECT_EQ(actual.map_y_count, 14);

  //double
}
