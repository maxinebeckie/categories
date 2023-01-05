-- chapter 2: types and functions

x :: Integer

	-- note Integer in Haskell is arbitrary-precision. 

-- consider the following function

f :: Bool -> Bool

	-- f may return True, False, or _|_, called bottom. Bottom represents a 
	-- 	nonterminating computation. Bottom is a member of any type.  
	-- 	Functions that may return bottom are partial, others are total. 
f = undefined 

	-- now f will return _|_.
	--  
	--  we will refer to the category of haskell functions as Hask, not Set.  
	--  however, sometimes we will confuse these for pragmatism. 

-- Denotational Semantics (v. Operational Semantics): consider the factorial

fact n = product [1..n]

-- on page 17..
