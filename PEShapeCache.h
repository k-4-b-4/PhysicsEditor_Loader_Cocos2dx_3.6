//
//  PEShapeCache.h
//  MemoryCards_CPP
//  描述：加载PhysicsEditor 编辑的chipmunk Shapes
//  Created by lili on 14-9-1.
//
//
#ifndef __MemoryCards_CPP__PEShapeCache_X3_0__
#define __MemoryCards_CPP__PEShapeCache_X3_0__
#include <iostream>
#include "cocos2d.h"
#include <unordered_map>

NS_CC_BEGIN
class PhysicsBody;
class BodyDef;

class PEShapeCache : public Ref
{
//---------- クラスメソッド
public:

    // シングルトン取得
    static PEShapeCache *getInstance();

//---------- インスタンスメソッド
public:
    // plistを読み込む
    void addBodysWithFile(const std::string &plist);
    
    // キー経由でPhysicsBodyを取得
    PhysicsBody *getPhysicsBodyByName(const std::string name);
    
    // 読み込んだplistを破棄
    bool removeBodysWithFile(const std::string &plist);

    // 剛体情報を削除
    bool removeAllBodys();
    /**
     *  重置缓存
     */
    void reset();

private:
    bool safeReleaseBodyDef(BodyDef* bodyDef);

//---------- BodyDefを取得しておく場所
private:
    Map<std::string,BodyDef*> bodyDefs;
    
//----------演算子系
public:
    // コピーと代入を禁止する
    PEShapeCache(const PEShapeCache&) = delete;
    PEShapeCache(const PEShapeCache&&) = delete;
    PEShapeCache&& operator= (const PEShapeCache&) = delete;
    PEShapeCache&& operator= (const PEShapeCache&&) = delete;
private:
    PEShapeCache(); // コンストラクタ
    ~PEShapeCache();// デストラクタ
};
typedef enum
{
    SHAPE_POLYGON,
    SHAPE_CIRCLE
} PEShapeType;
class Polygon : public Ref
{
  public:
    Point* vertices;      //ポリゴン
    int numVertices;      //ポリゴン数
    float area;           //面積
    float mass;           //质量
    float momentum;       //扭力
};
class FixtureData : public Ref
{
  public:
    PEShapeType fixtureType;//形状类型
    float mass;             //质量；
    float elasticity;       //弹力
    float friction;         //摩擦力
    Point surfaceVelocity;  //初速度
    int collisionType;      //分类
    int group;              //组
    int layers;             //在的层
    float area;             //面积
    float momentum;         //扭力
    bool isSensor;          //是不是传感器
                            //for circles
    Point center;           //中心
    float radius;           //半径
                            //for polygons
    Vector<Polygon*> polygons;   //顶点数组
};



class BodyDef : public Ref
{
public:
    Point anchorPoint;    //锚点
    Vector<FixtureData*> fixtures; //配置表单
    float mass;           //质量
    float momentum;       //扭力
};
NS_CC_END
#endif /* defined(__MemoryCards_CPP__PEShapeCache_X3_0__) */
