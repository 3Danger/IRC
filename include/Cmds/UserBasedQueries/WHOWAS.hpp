#pragma once
#include "ACommand.hpp"

class WHOWAS : public ACommand {
private:
    WHOWAS();
    WHOWAS(WHOWAS const &that);
    WHOWAS& operator=(WHOWAS const &that);
public:
    WHOWAS(Server &Server) : ACommand("WHOWAS", Server) {}
    virtual ~WHOWAS() {}
    virtual int run(){
        if (_Arguments.empty()) {
            return _Initiator->updateReplyMessage(ERR_NEEDMOREPARAMS(_Name));
            
        }
        //code
    }
};/*
        Parameters: <nickname> [<count> [<server>]]

        Whowas asks for information about a nickname which no longer exists.
        This may either be due to a nickname change or the user leaving IRC.
        In response to this query, the server searches through its nickname
        history, looking for any nicks which are lexically the same (no wild
        card matching here).  The history is searched backward, returning the
        most recent entry first.  If there are multiple entries, up to
        <count> replies will be returned (or all of them if no <count>
        parameter is given).  If a non-positive number is passed as being
        <count>, then a full search is done.

        Numeric Replies:

        ERR_NONICKNAMEGIVEN             ERR_WASNOSUCHNICK
        RPL_WHOWASUSER                  RPL_WHOISSERVER
        RPL_ENDOFWHOWAS

        Examples:

        WHOWAS Wiz                      ; return all information in the nick
                                        history about nick "WiZ";

        WHOWAS Mermaid 9                ; return at most, the 9 most recent
                                        entries in the nick history for
                                        "Mermaid";

        WHOWAS Trillian 1 *.edu         ; return the most recent history for
                                        "Trillian" from the first server found
                                        to match "*.edu".
*/