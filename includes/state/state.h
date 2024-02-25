#ifndef STATE_H
#define STATE_H


class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};


#endif