//@authors : Team 20
#include <gtest/gtest.h>
#include "Network.h"
#include "random.h"
#include "Neurone.h"
#include "types.h"
#include <iostream>

RandomNumbers RNG; //----> #include "random.h has extern RandomNumbers RNG;

TEST(neuronetest,initialize){

	Neurone rs (RS);
	Neurone ib (IB);
	Neurone ch (CH);
	Neurone fs (FS);
	Neurone lts (LTS);

	EXPECT_EQ(-65,rs.get_c());
	EXPECT_EQ(-55,ib.get_c());
	EXPECT_EQ(-50,ch.get_c());
	EXPECT_EQ(-65,fs.get_c());
	EXPECT_EQ(-65,lts.get_c());

	EXPECT_EQ(8,rs.get_d());
	EXPECT_EQ(4,ib.get_d());
	EXPECT_EQ(2,ch.get_d());
	EXPECT_EQ(2,fs.get_d());
	EXPECT_EQ(2,lts.get_d());
	//relaxation
  EXPECT_EQ(-13,rs.get_relaxation());
	EXPECT_EQ(-13,ib.get_relaxation());
	EXPECT_EQ(-13,ch.get_relaxation());
	EXPECT_NEAR(fs.get_relaxation(),-16.25, 9.75);
	EXPECT_EQ(-16.25,lts.get_relaxation());
  //potentiel
	rs.calcul_potentiel();
	ib.calcul_potentiel();
	ch.calcul_potentiel();
	fs.calcul_potentiel();
	lts.calcul_potentiel();

  EXPECT_NEAR(rs.get_potentiel(),-68,15);
	EXPECT_NEAR(ib.get_potentiel(),-68,15);
	EXPECT_NEAR(ch.get_potentiel(),-68,15);
  EXPECT_NEAR(fs.get_potentiel(),-64.75,15.75);
	EXPECT_NEAR(lts.get_potentiel(),-64.75,6);
}

TEST(neuronetest,firing){

	Neurone rs (RS);
	Neurone lts (LTS);

	rs.set_potentiel(0);
	lts.set_potentiel(0);
	EXPECT_FALSE(rs.firing());
	EXPECT_FALSE(lts.firing());
	EXPECT_EQ(rs.get_firing_courant(),0);
	EXPECT_EQ(lts.get_firing_courant(),0);

	rs.set_potentiel(50);
	lts.set_potentiel(50);
	EXPECT_TRUE(rs.firing());
	EXPECT_TRUE(lts.firing());
	EXPECT_NEAR(rs.get_firing_courant(),0,15);
	EXPECT_NEAR(lts.get_firing_courant(),0,6);

}

TEST(neuronetest,update){
	Neurone rs (RS);

	rs.update(1);

	EXPECT_NEAR(rs.get_potentiel(),-68,15);
	EXPECT_EQ(-13,rs.get_relaxation());

	rs.update(1);

	EXPECT_NEAR(rs.get_potentiel(),-96.64,45.96);
	EXPECT_NEAR(rs.get_relaxation(),-13.126,0.18);

}
TEST(networkTest, initialize){
	Network net ({1,0,0,1,0},21,0.2,3);
	size_t ex (0);
	size_t in (0);
	for (size_t i(0); i<net.size();++i){
		if (net.get_neurones()[i]->get_coeff()== -1){
			++ in;
		}
		if (net.get_neurones()[i]->get_coeff()== 0.5){
			++ ex;
		}
	}
EXPECT_EQ(17,in);
EXPECT_EQ(4,ex);
}

TEST(networkTest, current){
	Network net ({1,0,0,1,0},10,0.2,3);
	std::vector<size_t> fneur;
	for (size_t i (0);i<net.size();++i){
		net.get_neurones()[i]->set_potentiel(50);
	}
	fneur = net.firing_neurones();
	//a continuer
}


TEST(networkTest, links){
	Network net ({1,0,0,1,0},10,0.2,3);
	net.clear_links();
	EXPECT_TRUE(net.add_link(0, 1));
	EXPECT_FALSE(net.add_link(0,1));
	EXPECT_FALSE(net.add_link(1,0));
	EXPECT_TRUE(net.add_link(2, 1));
	EXPECT_TRUE(net.add_link(2, 3));
	EXPECT_FALSE(net.add_link(10,0));
	EXPECT_FALSE(net.add_link(0,0));

}
TEST(networkTest,connectivity){
  Network net({1,0,0,1,0},100,0.2,2);
	net.clear_links();
  EXPECT_NEAR(net.random_connect(2),200,25);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
