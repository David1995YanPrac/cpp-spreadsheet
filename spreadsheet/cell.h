#pragma once

#include "common.h"
#include "formula.h"

#include <functional>
#include <unordered_set>
#include <optional>

class Sheet;

class Cell : public CellInterface {
public:
    Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

    bool IsReferenced() const;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    bool CheckForCyclicity(const Impl& impl) const;
    void DoInvalidCache(bool check_changes = false);

    std::unique_ptr<Impl> impl_;

    Sheet& sheet_;
    std::unordered_set<Cell*> left_nods_;
    std::unordered_set<Cell*> right_nods_;
};
