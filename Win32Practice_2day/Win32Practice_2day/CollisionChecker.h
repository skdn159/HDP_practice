#pragma once
class CollisionChecker
{
public:
    CollisionChecker();
    ~CollisionChecker();

    bool IsCircleCollsion();
    bool IsBoxCollision();
    bool IsBoxCircleCollision();
    bool IsRotationCollision();
};

