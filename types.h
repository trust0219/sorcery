#ifndef _TYPES_H_
#define _TYPES_H_

// NTA: No Trigger && Active
// HA : Have Active Ability
// TS: Turn Starts
// TE: Turn Ends
// MEB: Minion Enters Board
// MLB: Minoin Leaves Board
// ENC: Enchanted
enum class MinionType { NTA, HA, TS, TE, MEB, MLB, ENC };

// TS: Turn Starts
// TE: Turn Ends
// MEB: Minion Enters Board
// MLB: Minoin Leaves Board
enum class TriggerType { TS, TE, MEB, MLB };

// M: Minion
// S: Spell
// R: Ritual
// E: Enchantment
enum class CardType { M, S, R, E };
#endif
