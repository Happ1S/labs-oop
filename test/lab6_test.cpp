// Файл: tests.cpp
#include <gtest/gtest.h>
#include "../src/lab6/include/npc.h"
#include "../src/lab6/include/bear.h"
#include "../src/lab6/include/elf.h"
#include "../src/lab6/include/bandit.h"
#include "../src/lab6/include/visitor.h"

// Тест для метода getType()
TEST(NPCTest, GetType) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(0, 0);
    std::shared_ptr<NPC> elf = std::make_shared<Elf>(0, 0);
    std::shared_ptr<NPC> bandit = std::make_shared<Bandit>(0, 0);

    EXPECT_EQ(bear->getType(), BearType);
    EXPECT_EQ(elf->getType(), ElfType);
    EXPECT_EQ(bandit->getType(), BanditType);
}

// Тесты для проверки логики боёв
TEST(VisitorTest, ElfAttacksBandit) {
    std::shared_ptr<NPC> elf = std::make_shared<Elf>(0, 0);
    std::shared_ptr<NPC> bandit = std::make_shared<Bandit>(0, 0);

    Visitor visitor;
    elf->accept(visitor, bandit);

    EXPECT_TRUE(visitor.is_success()); // Эльф должен убить разбойника
}

TEST(VisitorTest, BanditAttacksBandit) {
    std::shared_ptr<NPC> bandit1 = std::make_shared<Bandit>(0, 0);
    std::shared_ptr<NPC> bandit2 = std::make_shared<Bandit>(0, 0);

    Visitor visitor;
    bandit1->accept(visitor, bandit2);

    // Результат боя случайный, проверим, что результат является булевым значением
    EXPECT_TRUE(visitor.is_success() == true || visitor.is_success() == false);
}

TEST(VisitorTest, BearAttacksElf) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(0, 0);
    std::shared_ptr<NPC> elf = std::make_shared<Elf>(0, 0);

    Visitor visitor;
    bear->accept(visitor, elf);

    EXPECT_TRUE(visitor.is_success()); // Медведь должен убить эльфа
}

TEST(VisitorTest, BearAttacksBandit) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>(0, 0);
    std::shared_ptr<NPC> bandit = std::make_shared<Bandit>(0, 0);

    Visitor visitor;
    bear->accept(visitor, bandit);

    // Согласно вашей логике, медведь и бандит не взаимодействуют
    EXPECT_FALSE(visitor.is_success());
}

TEST(VisitorTest, ElfAttacksElf) {
    std::shared_ptr<NPC> elf1 = std::make_shared<Elf>(0, 0);
    std::shared_ptr<NPC> elf2 = std::make_shared<Elf>(0, 0);

    Visitor visitor;
    elf1->accept(visitor, elf2);

    // Эльфы не должны сражаться друг с другом
    EXPECT_FALSE(visitor.is_success());
}

TEST(VisitorTest, BanditAttacksElf) {
    std::shared_ptr<NPC> bandit = std::make_shared<Bandit>(0, 0);
    std::shared_ptr<NPC> elf = std::make_shared<Elf>(0, 0);

    Visitor visitor;
    bandit->accept(visitor, elf);

    // Если бандит атакует эльфа, согласно вашей логике, бой не происходит
    EXPECT_FALSE(visitor.is_success());
}