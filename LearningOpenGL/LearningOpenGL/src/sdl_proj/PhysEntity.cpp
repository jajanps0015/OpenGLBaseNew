#include <PhysEntity.h>
#include <managers/PhysicsManager.h>

namespace FOGrP
{
    void PhysEntity::AddCollider(Collider* collider, Vector2 localPos)
    {
        collider->Parent(this);
        collider->Position(localPos);

        mColliders.push_back(collider);

        if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
        {
            float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
            float dist = 0.0f;

            for (int i = 1; i < mColliders.size(); i++)
            {
                dist = mColliders[i]->GetFurthestPoint().Magnitude();

                if (dist > furthestDistance)
                {
                    furthestDistance = dist;
                }
            }

            delete mBroadPhaseCollider; mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
            mBroadPhaseCollider->Parent(this);
            mBroadPhaseCollider->Position(Vec2_Zero);
        };
    }

    bool PhysEntity::IgnoreCollisions()
    {
        return false;
    }

    PhysEntity::PhysEntity()
    {
        mBroadPhaseCollider = nullptr;
        mId = 0;
    }


    PhysEntity::~PhysEntity()
    {
        if (mId != 0)
        {
            PhysicsManager::Instance()->UnregisterEntity(mId);
        }
        for (auto c : mColliders)
        {
            delete c;
        }

        mColliders.clear();
        delete mBroadPhaseCollider;
    }

    unsigned long PhysEntity::GetId()
    {
        return mId;
    }

    bool PhysEntity::CheckCollision(PhysEntity* other)
    {
        if (IgnoreCollisions() || other->IgnoreCollisions())
        {
            return false;
        }

        bool narrowPhaseCheck = false;
        if (mBroadPhaseCollider && other->mBroadPhaseCollider)
        {
            narrowPhaseCheck = ColliderVsColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
        }
        else
        {
            narrowPhaseCheck = true;
        }

        if (narrowPhaseCheck)
        {
            for (int i = 0; i < mColliders.size(); i++)
            {
                for (int j = 0; j < other->mColliders.size(); j++)
                {
                    if (ColliderVsColliderCheck(mColliders[i], other->mColliders[j]))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void PhysEntity::Render()
    {
        for (auto c : mColliders)
        {
            c->Render();
        }

        if (mBroadPhaseCollider)
        {
            mBroadPhaseCollider->Render();
        }
    }

    void PhysEntity::Hit(PhysEntity* other)
    {

    }
}