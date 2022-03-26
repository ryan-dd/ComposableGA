#ifndef DEFAULTPARENTSELECTOR_H
#define DEFAULTPARENTSELECTOR_H

class DefaultParentSelector
{
public:
    DefaultParentSelector(){};
    // TODO change double to sortable concept
    void selectParents(std::vector<std::vector<entt::entity>>& population, const std::vector<double>& scores){};

};

#endif // DEFAULTPARENTSELECTOR_H
