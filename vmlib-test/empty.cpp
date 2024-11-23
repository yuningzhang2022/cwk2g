#include <catch2/catch_amalgamated.hpp>
#include "../vmlib/mat22.hpp"
#include "../vmlib/mat33.hpp"
#include "../vmlib/mat44.hpp"


//====== test ========

TEST_CASE("Mat22f multiplication tests", "[mat22]")
{
    SECTION("Identity matrix multiplication")
    {
        Mat22f identity = { 1.f, 0.f, 0.f, 1.f };
        Mat22f result = identity * identity;

        REQUIRE(result._00 == identity._00);
        REQUIRE(result._01 == identity._01);
        REQUIRE(result._10 == identity._10);
        REQUIRE(result._11 == identity._11);
    }

    SECTION("Matrix-vector multiplication with identity")
    {
        Mat22f identity = { 1.f, 0.f, 0.f, 1.f };
        Vec2f testVec = { 2.f, 3.f };
        Vec2f result = identity * testVec;

        REQUIRE(result.x == testVec.x);
        REQUIRE(result.y == testVec.y);
    }

    SECTION("General matrix multiplication")
    {
        Mat22f mat1 = { 2.f, -1.f,
                       1.f,  3.f };
        Mat22f mat2 = { 1.f,  2.f,
                       3.f,  4.f };
        Mat22f result = mat1 * mat2;

        REQUIRE(result._00 == Catch::Approx(-1.f));
        REQUIRE(result._01 == Catch::Approx(0.f));
        REQUIRE(result._10 == Catch::Approx(10.f));
        REQUIRE(result._11 == Catch::Approx(14.f));
    }
}

TEST_CASE("Mat22f rotation tests", "[mat22]")
{
    SECTION("Rotation 90 degrees")
    {
        float const pi = 3.14159265359f;
        Mat22f rot = make_rotation_2d(pi / 2.f);
        Vec2f point = { 1.f, 0.f };
        Vec2f rotated = rot * point;

        REQUIRE(rotated.x == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.y == Catch::Approx(1.f).margin(0.00001));
    }

    SECTION("Rotation 180 degrees")
    {
        float const pi = 3.14159265359f;
        Mat22f rot = make_rotation_2d(pi);
        Vec2f point = { 1.f, 0.f };
        Vec2f rotated = rot * point;

        REQUIRE(rotated.x == Catch::Approx(-1.f).margin(0.00001));
        REQUIRE(rotated.y == Catch::Approx(0.f).margin(0.00001));
    }
}

TEST_CASE("Mat22f special cases", "[mat22]")
{
    SECTION("Zero vector transformation")
    {
        Mat22f mat = { 2.f, 3.f,
                      4.f, 5.f };
        Vec2f zeroVec = { 0.f, 0.f };
        Vec2f result = mat * zeroVec;

        REQUIRE(result.x == 0.f);
        REQUIRE(result.y == 0.f);
    }

    SECTION("Identity transformation")
    {
        Mat22f identity = { 1.f, 0.f,
                           0.f, 1.f };
        Vec2f vec = { 3.f, 4.f };
        Vec2f result = identity * vec;

        REQUIRE(result.x == vec.x);
        REQUIRE(result.y == vec.y);
    }
}

// ======== test Mat33 ============

TEST_CASE("Mat33f operations", "[Mat33f]") {
    SECTION("Matrix-vector multiplication") {
        Mat33f mat = {
            1.f, 2.f, 3.f,
            4.f, 5.f, 6.f,
            7.f, 8.f, 9.f
        };
        Vec3f vec = { 1.f, 0.f, 0.f };
        Vec3f result = mat * vec;

        REQUIRE(result.x == Catch::Approx(1.f));
        REQUIRE(result.y == Catch::Approx(4.f));
        REQUIRE(result.z == Catch::Approx(7.f));
    }

    SECTION("Identity matrix-vector multiplication") {
        Mat33f identity = kIdentity33f;
        Vec3f vec = { 1.f, 2.f, 3.f };
        Vec3f result = identity * vec;

        REQUIRE(result.x == Catch::Approx(vec.x));
        REQUIRE(result.y == Catch::Approx(vec.y));
        REQUIRE(result.z == Catch::Approx(vec.z));
    }

    SECTION("mat44_to_mat33 conversion") {
        Mat44f mat44 = {
            1.f, 2.f, 3.f, 4.f,
            5.f, 6.f, 7.f, 8.f,
            9.f, 10.f, 11.f, 12.f,
            13.f, 14.f, 15.f, 16.f
        };
        Mat33f mat33 = mat44_to_mat33(mat44);

        REQUIRE(mat33(0, 0) == Catch::Approx(1.f));
        REQUIRE(mat33(0, 1) == Catch::Approx(2.f));
        REQUIRE(mat33(0, 2) == Catch::Approx(3.f));
        REQUIRE(mat33(1, 0) == Catch::Approx(5.f));
        REQUIRE(mat33(1, 1) == Catch::Approx(6.f));
        REQUIRE(mat33(1, 2) == Catch::Approx(7.f));
        REQUIRE(mat33(2, 0) == Catch::Approx(9.f));
        REQUIRE(mat33(2, 1) == Catch::Approx(10.f));
        REQUIRE(mat33(2, 2) == Catch::Approx(11.f));
    }
}

// ======== test Mat44 ============

TEST_CASE("Matrix multiplication tests", "[mat44]")
{
    SECTION("Identity matrix multiplication")
    {
        Mat44f result = kIdentity44f * kIdentity44f;
        for (std::size_t i = 0; i < 4; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                REQUIRE(result(i, j) == kIdentity44f(i, j));
            }
        }
    }

    SECTION("Matrix-vector multiplication with identity")
    {
        Vec4f testVec = { 1.f, 2.f, 3.f, 1.f };
        Vec4f result = kIdentity44f * testVec;
        REQUIRE(result.x == testVec.x);
        REQUIRE(result.y == testVec.y);
        REQUIRE(result.z == testVec.z);
        REQUIRE(result.w == testVec.w);
    }
}

TEST_CASE("Rotation matrix tests", "[mat44]")
{
    SECTION("Rotation X 90 degrees")
    {
        float const pi = 3.14159265359f;
        Mat44f rotX = make_rotation_x(pi / 2.f);
        Vec4f point = { 0.f, 1.f, 0.f, 1.f };
        Vec4f rotated = rotX * point;

        REQUIRE(rotated.x == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.y == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.z == Catch::Approx(1.f).margin(0.00001));
        REQUIRE(rotated.w == 1.f);
    }

    SECTION("Rotation Y 90 degrees")
    {
        float const pi = 3.14159265359f;
        Mat44f rotY = make_rotation_y(pi / 2.f);
        Vec4f point = { 1.f, 0.f, 0.f, 1.f };
        Vec4f rotated = rotY * point;

        REQUIRE(rotated.x == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.y == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.z == Catch::Approx(-1.f).margin(0.00001));
        REQUIRE(rotated.w == 1.f);
    }

    SECTION("Rotation Z 90 degrees")
    {
        float const pi = 3.14159265359f;
        Mat44f rotZ = make_rotation_z(pi / 2.f);
        Vec4f point = { 1.f, 0.f, 0.f, 1.f };
        Vec4f rotated = rotZ * point;

        REQUIRE(rotated.x == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.y == Catch::Approx(1.f).margin(0.00001));
        REQUIRE(rotated.z == Catch::Approx(0.f).margin(0.00001));
        REQUIRE(rotated.w == 1.f);
    }
}

TEST_CASE("Translation matrix tests", "[mat44]")
{
    SECTION("Basic translation")
    {
        Vec3f trans = { 1.f, 2.f, 3.f };
        Mat44f transMat = make_translation(trans);
        Vec4f point = { 0.f, 0.f, 0.f, 1.f };
        Vec4f translated = transMat * point;

        REQUIRE(translated.x == trans.x);
        REQUIRE(translated.y == trans.y);
        REQUIRE(translated.z == trans.z);
        REQUIRE(translated.w == 1.f);
    }
}

TEST_CASE("Scaling matrix tests", "[mat44]")
{
    SECTION("Uniform scaling")
    {
        Mat44f scale = make_scaling(2.f, 2.f, 2.f);
        Vec4f point = { 1.f, 1.f, 1.f, 1.f };
        Vec4f scaled = scale * point;

        REQUIRE(scaled.x == 2.f);
        REQUIRE(scaled.y == 2.f);
        REQUIRE(scaled.z == 2.f);
        REQUIRE(scaled.w == 1.f);
    }

    SECTION("Non-uniform scaling")
    {
        Mat44f scale = make_scaling(1.f, 2.f, 3.f);
        Vec4f point = { 1.f, 1.f, 1.f, 1.f };
        Vec4f scaled = scale * point;

        REQUIRE(scaled.x == 1.f);
        REQUIRE(scaled.y == 2.f);
        REQUIRE(scaled.z == 3.f);
        REQUIRE(scaled.w == 1.f);
    }
}

TEST_CASE("Perspective projection matrix tests", "[mat44]")
{
    SECTION("Basic perspective test")
    {
        float const pi = 3.14159265359f;
        float fov = pi / 2.f; // 90 degrees
        float aspect = 16.f / 9.f;
        float near = 0.1f;
        float far = 100.f;

        Mat44f proj = make_perspective_projection(fov, aspect, near, far);
        Vec4f point = { 0.f, 0.f, -near, 1.f }; // Point on near plane
        Vec4f projected = proj * point;

        REQUIRE(projected.z / projected.w == Catch::Approx(-1.0f).margin(0.00001));
    }
}

TEST_CASE("Matrix transpose test", "[mat44]")
{
    SECTION("Transpose identity matrix")
    {
        Mat44f transposed = transpose(kIdentity44f);
        for (std::size_t i = 0; i < 4; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                REQUIRE(transposed(i, j) == kIdentity44f(i, j));
            }
        }
    }

    SECTION("Transpose general matrix")
    {
        Mat44f original = {
            1.f, 2.f, 3.f, 4.f,
            5.f, 6.f, 7.f, 8.f,
            9.f, 10.f, 11.f, 12.f,
            13.f, 14.f, 15.f, 16.f
        };

        Mat44f transposed = transpose(original);

        for (std::size_t i = 0; i < 4; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                REQUIRE(transposed(i, j) == original(j, i));
            }
        }
    }
}
