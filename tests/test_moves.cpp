#include "gtest/gtest.h"
#include "toml.hpp"
#include "cube.hpp"
#include "moves.hpp"
#include "common.hpp"

#include <array>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

using namespace std;

uint32_t string2colornum(string str) {
    if(str == "W") { return WHITE; }
    else if(str == "Y") { return YELLOW; }
    else if(str == "G") { return GREEN; }
    else if(str == "B") { return BLUE; }
    else if(str == "R") { return RED; }
    else if(str == "O") { return ORANGE; }
    else { throw invalid_argument("Unknown color read from TOML: " + str + "\n"); }
}

void set_face(toml::v3::node_view<toml::v3::node> node_view, uint32_t &face) {
    uint8_t i = 0;
    array<uint8_t, 9> shifts = {
        TOP_LEFT,
        TOP_MIDDLE,
        TOP_RIGHT,
        MIDDLE_LEFT,
        CENTER,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        BOTTOM_RIGHT
    };
    
    if(node_view.is_array()) {
        toml::array *toml_arr = node_view.as_array();
        for(auto&& elem : *toml_arr) {
            if(elem.is_string()) {
                face |= (string2colornum(*elem.value<std::string>()) << shifts[i++]);
            } else {
                cerr << "Non string element found when string element expected!" << endl;
            }
        }
    } else {
        //? add a helpful message
    }
}

array<uint32_t, 6> state(string toml_path) {
    array<uint8_t, 9> shifts = {
        TOP_LEFT,
        TOP_MIDDLE,
        TOP_RIGHT,
        MIDDLE_LEFT,
        CENTER,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        BOTTOM_RIGHT
    };
    
    try {
        toml::table solution = toml::parse_file(toml_path);
        
        uint32_t top = 0, front = 0, left = 0, right = 0, back = 0, bottom = 0;
        uint8_t u = 0, d = 0, l = 0, r = 0, f = 0, b = 0;

        if(auto node_view = solution["up"]) { set_face(node_view, top); }
        if(auto node_view = solution["front"]) { set_face(node_view, front); }
        if(auto node_view = solution["left"]) { set_face(node_view, left); }
        if(auto node_view = solution["right"]) { set_face(node_view, right); }
        if(auto node_view = solution["back"]) { set_face(node_view, back); }
        if(auto node_view = solution["down"]) { set_face(node_view, bottom); }

        return {top, front, left, right, back, bottom};
    } catch (const toml::parse_error& err) {
        cerr << "Error parsing TOML file: " << err << std::endl;
        return {0, 0, 0, 0, 0, 0};
    }
}

class MoveTest : public ::testing::Test {
protected:
    Cube solved;

    void SetUp() override {
        // No setup required for now
    }
};

TEST_F(MoveTest, solved) {
    array<uint32_t, 6> sol = state("solutions/solved/solved.toml");
    array<uint32_t, 6> sat = solved.__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, U) {
    array<uint32_t, 6> sol = state("solutions/faces/U.toml");
    array<uint32_t, 6> sat = solved.U().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, U_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/U_prime.toml");
    array<uint32_t, 6> sat = solved.U_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, U2) {
    array<uint32_t, 6> sol = state("solutions/faces/U2.toml");
    array<uint32_t, 6> sat = solved.U2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, D) {
    array<uint32_t, 6> sol = state("solutions/faces/D.toml");
    array<uint32_t, 6> sat = solved.D().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, D_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/D_prime.toml");
    array<uint32_t, 6> sat = solved.D_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, D2) {
    array<uint32_t, 6> sol = state("solutions/faces/D2.toml");
    array<uint32_t, 6> sat = solved.D2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, L) {
    array<uint32_t, 6> sol = state("solutions/faces/L.toml");
    array<uint32_t, 6> sat = solved.L().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, L_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/L_prime.toml");
    array<uint32_t, 6> sat = solved.L_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, L2) {
    array<uint32_t, 6> sol = state("solutions/faces/L2.toml");
    array<uint32_t, 6> sat = solved.L2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, R) {
    array<uint32_t, 6> sol = state("solutions/faces/R.toml");
    array<uint32_t, 6> sat = solved.R().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, R_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/R_prime.toml");
    array<uint32_t, 6> sat = solved.R_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, R2) {
    array<uint32_t, 6> sol = state("solutions/faces/R2.toml");
    array<uint32_t, 6> sat = solved.R2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, F) {
    array<uint32_t, 6> sol = state("solutions/faces/F.toml");
    array<uint32_t, 6> sat = solved.F().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, F_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/F_prime.toml");
    array<uint32_t, 6> sat = solved.F_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, F2) {
    array<uint32_t, 6> sol = state("solutions/faces/F2.toml");
    array<uint32_t, 6> sat = solved.F2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, B) {
    array<uint32_t, 6> sol = state("solutions/faces/B.toml");
    array<uint32_t, 6> sat = solved.B().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, B_prime) {
    array<uint32_t, 6> sol = state("solutions/faces/B_prime.toml");
    array<uint32_t, 6> sat = solved.B_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, B2) {
    array<uint32_t, 6> sol = state("solutions/faces/B2.toml");
    array<uint32_t, 6> sat = solved.B2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, M) {
    array<uint32_t, 6> sol = state("solutions/slices/M.toml");
    array<uint32_t, 6> sat = solved.M().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, M_prime) {
    array<uint32_t, 6> sol = state("solutions/slices/M_prime.toml");
    array<uint32_t, 6> sat = solved.M_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, M2) {
    array<uint32_t, 6> sol = state("solutions/slices/M2.toml");
    array<uint32_t, 6> sat = solved.M2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, E) {
    array<uint32_t, 6> sol = state("solutions/slices/E.toml");
    array<uint32_t, 6> sat = solved.E().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, E_prime) {
    array<uint32_t, 6> sol = state("solutions/slices/E_prime.toml");
    array<uint32_t, 6> sat = solved.E_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, E2) {
    array<uint32_t, 6> sol = state("solutions/slices/E2.toml");
    array<uint32_t, 6> sat = solved.E2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, S) {
    array<uint32_t, 6> sol = state("solutions/slices/S.toml");
    array<uint32_t, 6> sat = solved.S().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, S_prime) {
    array<uint32_t, 6> sol = state("solutions/slices/S_prime.toml");
    array<uint32_t, 6> sat = solved.S_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, S2) {
    array<uint32_t, 6> sol = state("solutions/slices/S2.toml");
    array<uint32_t, 6> sat = solved.S2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, X) {
    array<uint32_t, 6> sol = state("solutions/rotation/X.toml");
    array<uint32_t, 6> sat = solved.X().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, X_prime) {
    array<uint32_t, 6> sol = state("solutions/rotation/X_prime.toml");
    array<uint32_t, 6> sat = solved.X_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, X2) {
    array<uint32_t, 6> sol = state("solutions/rotation/X2.toml");
    array<uint32_t, 6> sat = solved.X2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Y) {
    array<uint32_t, 6> sol = state("solutions/rotation/Y.toml");
    array<uint32_t, 6> sat = solved.Y().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Y_prime) {
    array<uint32_t, 6> sol = state("solutions/rotation/Y_prime.toml");
    array<uint32_t, 6> sat = solved.Y_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Y2) {
    array<uint32_t, 6> sol = state("solutions/rotation/Y2.toml");
    array<uint32_t, 6> sat = solved.Y2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Z) {
    array<uint32_t, 6> sol = state("solutions/rotation/Z.toml");
    array<uint32_t, 6> sat = solved.Z().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Z_prime) {
    array<uint32_t, 6> sol = state("solutions/rotation/Z_prime.toml");
    array<uint32_t, 6> sat = solved.Z_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, Z2) {
    array<uint32_t, 6> sol = state("solutions/rotation/Z2.toml");
    array<uint32_t, 6> sat = solved.Z2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, u) {
    array<uint32_t, 6> sol = state("solutions/wide/u.toml");
    array<uint32_t, 6> sat = solved.u().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, u_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/u_prime.toml");
    array<uint32_t, 6> sat = solved.u_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, u2) {
    array<uint32_t, 6> sol = state("solutions/wide/u2.toml");
    array<uint32_t, 6> sat = solved.u2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, d) {
    array<uint32_t, 6> sol = state("solutions/wide/d.toml");
    array<uint32_t, 6> sat = solved.d().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, d_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/d_prime.toml");
    array<uint32_t, 6> sat = solved.d_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, d2) {
    array<uint32_t, 6> sol = state("solutions/wide/d2.toml");
    array<uint32_t, 6> sat = solved.d2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, l) {
    array<uint32_t, 6> sol = state("solutions/wide/l.toml");
    array<uint32_t, 6> sat = solved.l().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, l_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/l_prime.toml");
    array<uint32_t, 6> sat = solved.l_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, l2) {
    array<uint32_t, 6> sol = state("solutions/wide/l2.toml");
    array<uint32_t, 6> sat = solved.l2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, r) {
    array<uint32_t, 6> sol = state("solutions/wide/r.toml");
    array<uint32_t, 6> sat = solved.r().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, r_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/r_prime.toml");
    array<uint32_t, 6> sat = solved.r_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, r2) {
    array<uint32_t, 6> sol = state("solutions/wide/r2.toml");
    array<uint32_t, 6> sat = solved.r2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, f) {
    array<uint32_t, 6> sol = state("solutions/wide/f.toml");
    array<uint32_t, 6> sat = solved.f().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, f_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/f_prime.toml");
    array<uint32_t, 6> sat = solved.f_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, f2) {
    array<uint32_t, 6> sol = state("solutions/wide/f2.toml");
    array<uint32_t, 6> sat = solved.f2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, b) {
    array<uint32_t, 6> sol = state("solutions/wide/b.toml");
    array<uint32_t, 6> sat = solved.b().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, b_prime) {
    array<uint32_t, 6> sol = state("solutions/wide/b_prime.toml");
    array<uint32_t, 6> sat = solved.b_prime().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, b2) {
    array<uint32_t, 6> sol = state("solutions/wide/b2.toml");
    array<uint32_t, 6> sat = solved.b2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, checkers1) {
    array<uint32_t, 6> sol = state("solutions/composite/checkers.toml");
    array<uint32_t, 6> sat = solved.R2().L2().F2().B2().U2().D2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, checkers2) {
    array<uint32_t, 6> sol = state("solutions/composite/checkers.toml");
    array<uint32_t, 6> sat = solved.M2().E2().S2().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, scramble1) {
    array<uint32_t, 6> sol = state("solutions/composite/scramble.toml");
    array<uint32_t, 6> sat = solved.U2().R2().D().F_prime().R2().B2().D().R_prime().D2().B_prime().R2().F2().D2().R2().L2().B().L2().U2().B().__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}

TEST_F(MoveTest, scramble2) {
    array<uint32_t, 6> sol = state("solutions/composite/scramble.toml");
    vector<string> moves = {moves::U2, moves::R2, moves::D, moves::F_prime, moves::R2, moves::B2, moves::D, moves::R_prime, moves::D2, moves::B_prime, moves::R2, moves::F2, moves::D2, moves::R2, moves::L2, moves::B, moves::L2, moves::U2, moves::B};
    array<uint32_t, 6> sat = solved.apply_moves(moves).__get_state();

    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(sol[i] == sat[i]);
    }
}
