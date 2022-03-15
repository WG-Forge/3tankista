#pragma once

#include <cassert>
#include <stack>

///-------------------------------------------------------------------------------------------------
/// Def:	BEGIN_TRANSITION_TABLE
///
/// Summary:	A macro that defines begining of the transition table. Only use
/// that one once!
///
/// Author:	Tobias Stein
///
/// Date:	10/10/2017
///-------------------------------------------------------------------------------------------------
#define BEGIN_TRANSITION_TABLE                                                                                         \
    virtual const SimpleFSM_TransitionTableEntry* GetTransitionTable(size_t& transitioncount) const override           \
    {                                                                                                                  \
        static const SimpleFSM_TransitionTableEntry TRANSITION_TABLE[] = {

///-------------------------------------------------------------------------------------------------
/// Def:	TRANSITION_ENTRY(from, to, onEnter, onLeave, code)
///
/// Summary:	A macro that defines a transition table entry. A valid entry is
/// a tripple of two states 'from' and 'to' as well as an transition code. this
/// code must be between 0 - 255. You can add multiple of this TRANSITION_ENTRY
/// in succeeding sequence between a BEGIN_TRANSITION_TABLE and TRANSITION_ENTRY
/// macro to setup a transition table. Optionally there can be a 'onLeave'
/// and/or 'onEnter' procedure be specified. 'onLeave' will be executed when
/// leaving the 'from' state and 'onEnter' will be executed when entering 'to'
/// state. Use 'NO_ONENTER_PROC' and 'NO_ONLEAVE_PROC' macro to specify that
/// there are no 'onEnter' and/or 'onLeave'.
///
/// Author:	Tobias Stein
///
/// Date:	10/10/2017
///-------------------------------------------------------------------------------------------------
#define TRANSITION_ENTRY(from, to, onEnter, onLeave, code)                                                             \
    { (SimpleFSM_State)(&from),                                                                                        \
      (SimpleFSM_State)(&to),                                                                                          \
      code,                                                                                                            \
      (SimpleFSM_State)(&onEnter),                                                                                     \
      (SimpleFSM_State)(&onLeave) },

///-------------------------------------------------------------------------------------------------
/// Def:	BEGIN_TRANSITION_TABLE
///
/// Summary:	A macro that defines end of the transition table. Only use that
/// one once!
///
/// Author:	Tobias Stein
///
/// Date:	10/10/2017
///-------------------------------------------------------------------------------------------------
#define END_TRANSITION_TABLE                                                                                           \
    {                                                                                                                  \
        nullptr, nullptr, NULL_TRANSITION, nullptr, nullptr                                                            \
    }                                                                                                                  \
    }                                                                                                                  \
    ;                                                                                                                  \
                                                                                                                       \
    static const size_t TRANSITION_TABLE_LEN = (sizeof(TRANSITION_TABLE) / sizeof(TRANSITION_TABLE[0])) - 1;           \
                                                                                                                       \
    transitioncount = TRANSITION_TABLE_LEN;                                                                            \
    return TRANSITION_TABLE;                                                                                           \
    }

///-------------------------------------------------------------------------------------------------
/// Def:	SET_STATE(state)
///
/// Summary:	A macro that should be used to set the state machine into a
/// certain state. When a new object of SimpleFSM class is created the initial
/// state will be zero, that is, UpdateStateMachine won't have any effect until
/// SET_STATE() was called.
///
/// Author:	Tobias Stein
///
/// Date:	10/10/2017
///
/// Parameters:
/// state - 	The state.
///-------------------------------------------------------------------------------------------------

#define SET_STATE(state) this->m_ActiveState = (SimpleFSM_State)(&state);

using SimpleFSM_TransitionCode                            = unsigned char;
static constexpr SimpleFSM_TransitionCode NULL_TRANSITION = 0xff;

class SimpleFSM;
typedef void (SimpleFSM::*SimpleFSM_State)();

#define NULL_STATE SimpleFSM::__NULL_STATE
#define NO_ONENTER_PROC SimpleFSM::__NULL_ON_ENTER
#define NO_ONLEAVE_PROC SimpleFSM::__NULL_ON_LEAVE

struct SimpleFSM_TransitionTableEntry
{
    SimpleFSM_State thisState;
    SimpleFSM_State nextState;

    SimpleFSM_TransitionCode code;

    SimpleFSM_State onEnter;
    SimpleFSM_State onLeave;
};

class SimpleFSM
{
    using StateStack = std::stack<SimpleFSM_TransitionCode>;

private:
    StateStack stateStack;

    SimpleFSM_State activeState;

protected:
    virtual const SimpleFSM_TransitionTableEntry* GetTransitionTable(std::size_t& transitionCount) const = 0;

public:
    // Defines null state, onEnter and onLeave callbacks
    void __NULL_STATE() {}
    void __NULL_ON_ENTER() {}
    void __NULL_ON_LEAVE() {}

    SimpleFSM()
        : activeState(&SimpleFSM::__NULL_STATE)
    {
    }

    virtual ~SimpleFSM() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	inline SimpleFSM_TransitionCode SimpleFSM::GetActiveState() const
    ///
    /// Summary:	Gets the current active state.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	21/10/2017
    ///
    /// Returns:	The active state.
    ///-------------------------------------------------------------------------------------------------
    inline SimpleFSM_TransitionCode GetActiveState() const
    {
        return (this->stateStack.empty() == false ? this->stateStack.top() : NULL_TRANSITION);
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	inline void SimpleFSM::UpdateStateMachine()
    ///
    /// Summary:	Updates the state machine.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	10/10/2017
    ///-------------------------------------------------------------------------------------------------
    inline void UpdateStateMachine()
    {
        if (this->activeState != nullptr)
        {
            (this->*activeState)();
        }
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	void SimpleFSM::ChangeState(SimpleFSM_TransitionCode code)
    ///
    /// Summary:	Change the current active state to a successor state by a
    /// given code. This won't push the old state onto the stack, but change the
    /// current top state.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	10/10/2017
    ///
    /// Parameters:
    /// code - 	The code.
    ///-------------------------------------------------------------------------------------------------
    void ChangeState(SimpleFSM_TransitionCode code)
    {
        if (code == NULL_TRANSITION)
            return;

        if (this->stateStack.empty() == false)
        {
            // change active state
            this->stateStack.pop();
            this->stateStack.push(code);
        }
        else
        {
            // push initial state
            this->stateStack.push(code);
        }

        std::size_t                           transitionCount = 0;
        const SimpleFSM_TransitionTableEntry* transitionTable = this->GetTransitionTable(transitionCount);

        for (std::size_t i = 0; i < transitionCount; ++i)
        {
            if ((this->activeState == transitionTable[i].thisState) && (code == transitionTable[i].code))
            {
                // onLeave proc
                if (transitionTable[i].onLeave != nullptr)
                {
                    (this->*(transitionTable[i].onLeave))();
                }

                // onEnter proc
                if (transitionTable[i].onEnter != nullptr)
                {
                    (this->*(transitionTable[i].onEnter))();
                }

                this->activeState = transitionTable[i].nextState;
                return;
            }
        }

        assert(false && "Invalid state transition!");
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	void SimpleFSM::PushState(SimpleFSM_TransitionCode code)
    ///
    /// Summary:	Change the current active state to a successor state by a
    /// given code. This operation will push the old state onto the state stack.
    /// The old previouse state can be restored by simply using the PopState
    /// method.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	21/10/2017
    ///
    /// Parameters:
    /// code - 	The code.
    ///-------------------------------------------------------------------------------------------------
    void PushState(SimpleFSM_TransitionCode code)
    {
        // push new active state onto of the stack
        this->stateStack.push(code);

        // change to new state
        this->ChangeState(code);
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	void SimpleFSM::PopState(bool activeOldState = true)
    ///
    /// Summary:	Pops the current active state from stack and restores the
    /// previouse one. If there is no previous state the NULL_STATE will be
    /// active. If activeOldState flag is false, only the top state will be
    /// popped, but the previous state won't be re-activated.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	21/10/2017
    ///-------------------------------------------------------------------------------------------------
    void PopState(bool activeOldState = true)
    {
        // remove active state from stack
        this->stateStack.pop();

        if (activeOldState == false)
            return;

        if (this->stateStack.empty() == false)
        {
            // change back to previous state
            this->ChangeState(this->stateStack.top());
        }
        else
        {
            // if there is no previous state, change to NULL_STATE
            this->activeState = &SimpleFSM::__NULL_STATE;
        }
    }

    ///-------------------------------------------------------------------------------------------------
    /// Fn:	void SimpleFSM::ResetFSM()
    ///
    /// Summary:	Resets the FSM. This will clear the state stack and put the
    /// FSM to null-state.
    ///
    /// Author:	Tobias Stein
    ///
    /// Date:	31/10/2017
    ///-------------------------------------------------------------------------------------------------
    void ResetFSM()
    {
        // clear state stack
        while (this->stateStack.empty() == false)
            this->stateStack.pop();

        // set null-state active
        this->activeState = &SimpleFSM::__NULL_STATE;
    }

}; // class SimpleFSM
