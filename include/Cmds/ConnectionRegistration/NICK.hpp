#include "ACommand.hpp"

class NICK : public ACommand {
private:
    NICK();
    NICK(NICK const &that);
    NICK& operator=(NICK const &that);
public:
    NICK(Server &Server) : ACommand("NICK", Server) {}
    virtual ~NICK() {}
    virtual int run(){
        std::vector<std::string> Tokens = ft::split(_Argument, " \b\t\n\v\f\r");
        std::string Nick;
        if (not Tokens.empty()) {
            Nick = Tokens[0];
        }
        if (Nick.empty()) {
            return _Initiator->setReplyMessage(ERR_NONICKNAMEGIVEN);
        }
        User *UserWithSameNick = _Server.getUserByNickName(Nick);
        if (UserWithSameNick and (UserWithSameNick not_eq _Initiator)) {
            return _Initiator->setReplyMessage(ERR_NICKNAMEINUSE(Nick));
        }
        if (Nick[0] == '-' or std::isdigit(Nick[0])) {
            ErroneusNickNameGiven:
            return _Initiator->setReplyMessage(ERR_ERRONEUSNICKNAME(Nick));
        }
        std::string SpecialCharacters = "`|^_-{}[]\\";
        for (size_t i = 1; i < Nick.length(); ++i) {
            if (not std::isalnum(Nick[i])
                && SpecialCharacters.find(Nick[i]) == SpecialCharacters.npos) {
                goto ErroneusNickNameGiven;
            }
        }
        _Initiator->setNickName(Nick);
        return 0;
    }
};/*
   Parameters: <nickname> [ <hopcount> ]

   NICK message is used to give user a nickname or change the previous
   one.  The <hopcount> parameter is only used by servers to indicate
   how far away a nick is from its home server.  A local connection has
   a hopcount of 0.  If supplied by a client, it must be ignored.

   If a NICK message arrives at a server which already knows about an
   identical nickname for another client, a nickname collision occurs.
   As a result of a nickname collision, all instances of the nickname
   are removed from the server's database, and a KILL command is issued
   to remove the nickname from all other server's database. If the NICK
   message causing the collision was a nickname change, then the
   original (old) nick must be removed as well.

   If the server recieves an identical NICK from a client which is
   directly connected, it may issue an ERR_NICKCOLLISION to the local
   client, drop the NICK command, and not generate any kills.

   Numeric Replies:

           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

   Example:

   NICK Wiz                        ; Introducing new nick "Wiz".

   :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.

*/
